module Data = struct
  type t =
    { size : int
    ; source : string
    }
  ;;

  let encode r =
    Json.Encode.(object_
      [ "size", r.size |> int
      ; "source", r.source |> string
      ]
    )
  ;;

  let make source size =
    match (size, source) with
    | (Some size, Some source) -> Some { size; source }
    | _ -> None
  ;;

  let eql a b =
    a.size = b.size
    && a.source = b.source
  ;;
end

type t =
  { id : string
  ; size : int
  ; original : Data.t option
  ; stat : Data.t option
  ; parsed : Data.t option
  ; children : t list
  ; reasons : (string list) list
  }
;;

let rec encode r =
  Json.Encode.(object_
    [ "id", r.id |> string
    ; "size", r.size |> int
    ; "original", r.original |> nullable Data.encode
    ; "stat", r.stat |> nullable Data.encode
    ; "parsed", r.parsed |> nullable Data.encode
    ; "children", r.children |> list encode
    ; "reasons", r.reasons |> list (list string)
    ]
  )
;;

let rec eql a b =
  a.id = b.id
  && a.size = b.size
  && a.stat = b.stat
  && a.original = b.original
  && a.parsed = b.parsed
  && Utils.List.isEqual ~eql a.children b.children ()
;;

let similar a b =
  a.id = b.id
;;

let hasId id entry =
  entry.id = id
;;

module FromModule = struct
  open Rationale.Option.Infix;;
  open Rationale.Function.Infix;;

  (* inspired by https://github.com/webpack-contrib/webpack-bundle-analyzer/blob/fe3c71e25238a1f9c557180404e9ef1d98e3801f/src/tree/utils.js#L10-L18 *)

  let getId = let separator = "/"
    in Utils.String.split "!"
      ||> Utils.Array.last
      ||> Utils.String.split separator
      ||> Array.map (fun part -> match part with
      | "~" -> "node_modules"
      | "(webpack)" -> "./node_modules/webpack"
      | part -> part
      )
      ||> Utils.Array.filter (fun part -> String.length part > 0)
      ||> Utils.Array.join separator
      ||> Js.String.replaceByRe [%re "/ \\+ \\d+ modules?$/"] ""
  ;;

  let nameEqual (a : WebpackModule.t) (b : WebpackModule.t) = getId(a.name) = getId(b.name);;

  let findMainSubmodule (module_: WebpackModule.t) = module_.modules
    >>= Utils.List.findOpt (nameEqual module_)
    |> Utils.defaultTo module_
  ;;

  let isMeaningfulModule (module_: WebpackModule.t) =
    module_.built && (
      module_ |> WebpackModule.hasCode
      || module_ |> WebpackModule.hasSubmodules
      || module_ |> WebpackModule.isEntryPoint |> not
    )
  ;;

  let rec make useParsedSize (module_ : WebpackModule.t) =
    let mainSubmodule = findMainSubmodule module_
    in let modules =
      module_.modules
      |> Utils.defaultTo []
      |> List.filter (Utils.Function.allPass [
          (!=) mainSubmodule;
          isMeaningfulModule
        ])
    in let statSize = mainSubmodule.source |> Utils.defaultTo "" |> String.length
    and id = getId mainSubmodule.name
    in
      { id
      ; size = (
        match (useParsedSize, mainSubmodule.parsedSize) with
        | (true, Some size) -> size
        | (true, None) ->
          (**
           * NOTE: JavaScript files without parsed size are most probably
           * built solely from re-exports, so they practically don't exist
           * in final bundle
           * The rest, like JSON, should be handled by webpack-enhanced-stats-plugin
           * See: https://github.com/erykpiast/webpack-enhanced-stats-plugin/issues/3
           *)
          let ext = String.split_on_char '.' id |> List.rev |> List.hd
          in (
            match ext with
            | "js" -> 0
            | _ -> statSize
          )
        | _ -> statSize
        )
      ; stat = Data.make
          mainSubmodule.source
          (Some statSize)
      ; original = Data.make
          mainSubmodule.originalSource
          mainSubmodule.originalSize
      ; parsed = Data.make
          mainSubmodule.parsedSource
          mainSubmodule.parsedSize
      ; children =
          modules
            |> List.map (make useParsedSize)
            |> List.filter (fun { children; size } -> size != 0 || (List.length children) != 0)
      ; reasons = mainSubmodule.reasons
        |> (List.map (fun (reason: WebpackReason.t) -> reason.moduleName))
        |> (List.filter Belt.Option.isSome)
        |> (List.map (Belt.Option.getUnsafe ||> getId))
        |> (Utils.List.uniq (==))
        |> (List.map (Utils.String.split "/" ||> Array.to_list))
      }
end

module FromChunk = struct
  let hashPattern = [%re "/\\/?(.*)(?:\\.[0-9a-f]+)(?:\\.chunk)?(\\.js|\\.css)/"]

  let removeHash filename =
    let separator = "/" in
    let split = Utils.String.split separator filename
      |> Array.to_list
      |> List.rev
    in match split with
    | hd :: tl -> (
        Js.String.unsafeReplaceBy2
        hashPattern
        (fun _ p1 p2 _ _ -> p1 ^ p2)
        hd
      )::tl
      |> List.rev
      |> Array.of_list
      |> Utils.Array.join separator
    | [] -> filename
  ;;

  let getFirstJsFilename (chunk : WebpackChunk.t) =
    chunk.files
    |> Utils.List.findOpt (Utils.String.endsWith ".js")
    |> Utils.defaultTo (List.nth chunk.files 0)
  ;;

  let getFilename = Rationale.Function.Infix.(getFirstJsFilename ||> removeHash);;

  let getId (chunk : WebpackChunk.t) =
    match chunk.names with
    | [] -> getFilename chunk
    | name :: _ -> name
  ;;

  let findChunkAsset (chunk : WebpackChunk.t) (assets : WebpackAsset.t list) =
    let firstJsFile = getFirstJsFilename chunk
    in Utils.List.findOpt
      (fun (asset : WebpackAsset.t) -> asset.name = firstJsFile)
      assets
  ;;

  let rec calculateOriginalSize modules =
    let size = modules
      |> List.map (fun (entry: t) ->
        let ownSize =
          match entry.original with
          | None -> 0
          | Some { size } -> size
        and submodulesSize = entry.children |> calculateOriginalSize |> Utils.defaultTo 0
        in ownSize + submodulesSize
      )
      |> List.fold_left (+) 0
    in
      if size = 0 then
        None
      else
        Some(size)
  ;;

  let rec findModuleWithSource modules = 
    List.fold_left
      (fun withSource module_ ->
        match (withSource) with
        | None -> (
          if WebpackModule.hasCode module_ then
            Some module_
          else
            match (module_.modules) with
            | None -> None
            | Some submodules -> findModuleWithSource submodules
        )
        | Some _ -> withSource
      )
      None
      modules
  ;;

  let make (assets : WebpackAsset.t list) (chunk : WebpackChunk.t) =
    let meaningfulModules = chunk.modules |> List.filter FromModule.isMeaningfulModule
    in let moduleWithSource = findModuleWithSource meaningfulModules
    in let useParsedSize = (
      match moduleWithSource with
      | Some module_ -> (
        match module_.parsedSize with
        | Some _ -> true
        | None -> false
      )
      | None -> false
    )
    in let () = Js.log ("moduleWithSource", moduleWithSource)
    in let () = Js.log ("useParsedSize", useParsedSize)
    in let modules = meaningfulModules  |> List.map (FromModule.make useParsedSize)
    and makeData = Data.make (Some "")
    and asset = findChunkAsset chunk assets
    in let parsed =
      match asset with
      | Some asset -> makeData (Some asset.size)
      | _ -> None
    in
      { id = getId chunk
      ; size = (
        match parsed with
        | Some { size } -> size
        | None -> chunk.size
      )
      ; original = calculateOriginalSize modules |> makeData
      ; stat = makeData (Some chunk.size)
      ; parsed = parsed
      ; children = modules
      ; reasons = []
      }
  ;;
end

module FromStats = struct
  let make (stat: WebpackStats.t) =
  stat.chunks |> List.map (FromChunk.make stat.assets);;
end
