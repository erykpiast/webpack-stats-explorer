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

  let nameEqual (a : WebpackModule.t) (b : WebpackModule.t) = a.name = b.name;;

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

  let rec make (module_ : WebpackModule.t) =
    let mainSubmodule = findMainSubmodule module_
    and getSubmodulesParsedSize =
      List.map
        (fun (module_: WebpackModule.t) -> module_.parsedSize |> Utils.defaultTo 0)
      ||> Utils.List.sumInt
    in let modules =
      module_.modules
      |> Utils.defaultTo []
      |> List.filter (Utils.Function.allPass [
          (!=) mainSubmodule;
          isMeaningfulModule
        ])
    in
      { id = getId mainSubmodule.name
      ; size = (
        match mainSubmodule.parsedSize with
        | Some size -> size + (modules |> getSubmodulesParsedSize)
        | None -> module_.size
      )
      ; stat = Data.make
          (Some (mainSubmodule.source |> Utils.defaultTo ""))
          (Some mainSubmodule.size)
      ; original = Data.make
          mainSubmodule.originalSource
          mainSubmodule.originalSize
      ; parsed = Data.make
          mainSubmodule.parsedSource
          mainSubmodule.parsedSize
      ; children = modules |> List.map make
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

  let calculateOriginalSize modules =
    let size = modules
      |> List.map (fun (entry: t) -> match entry.original with
        | None -> 0
        | Some { size } -> size
      )
      |> List.fold_left (+) 0
    in
      if size = 0 then
        None
      else
        Some(size)
  ;;

  let make (assets : WebpackAsset.t list) (chunk : WebpackChunk.t) =
    let modules = chunk.modules
      |> List.filter FromModule.isMeaningfulModule
      |> List.map FromModule.make
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
      }
  ;;
end

module FromStats = struct
  let make (stat: WebpackStats.t) =
  stat.chunks |> List.map (FromChunk.make stat.assets);;
end
