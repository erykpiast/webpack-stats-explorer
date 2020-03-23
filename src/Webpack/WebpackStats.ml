type compilation_error = string
type compilation_warning = string

type t =
  { assets : WebpackAsset.t list
  ; assetsByChunkName : WebpackAssetsGroup.t Js.Dict.t
  ; builtAt : int
  ; children : WebpackChild.t list
  ; chunks : WebpackChunk.t list
  ; entrypoints : WebpackEntrypoint.t Js.Dict.t
  ; errors : string list
  ; filteredAssets : int
  ; hash : string
  ; modules : WebpackModule.t list
  ; namedChunkGroups : WebpackEntrypoint.t Js.Dict.t
  ; outputPath : string
  ; time : int
  ; version : string
  ; warnings : string list
  }

let decode json =
  Json.Decode.
    { assets = json |> field "assets" (list WebpackAsset.decode)
    ; assetsByChunkName = json |> field "assetsByChunkName" (dict WebpackAssetsGroup.decode)
    ; builtAt = json |> field "builtAt" int
    ; children = json |> field "children" (list WebpackChild.decode)
    ; chunks = json |> field "chunks" (list WebpackChunk.decode)
    ; entrypoints = json |> field "entrypoints" (dict WebpackEntrypoint.decode)
    ; errors = json |> field "errors" (list string)
    ; filteredAssets = json |> field "filteredAssets" int
    ; hash = json |> field "hash" string
    ; modules = json |> field "modules" (list WebpackModule.decode)
    ; namedChunkGroups = json |> field "namedChunkGroups" (dict WebpackEntrypoint.decode)
    ; outputPath = json |> field "outputPath" string
    ; time = json |> field "time" int
    ; version = json |> field "version" string
    ; warnings = json |> field "warnings" (list string)
    }
;;

let encode r =
  Json.Encode.(
    object_
      [ "assets", r.assets |> list WebpackAsset.encode
      ; "assetsByChunkName", r.assetsByChunkName |> dict WebpackAssetsGroup.encode
      ; "builtAt", r.builtAt |> int
      ; "children", r.children |> list WebpackChild.encode
      ; "chunks", r.chunks |> list WebpackChunk.encode
      ; "entrypoints", r.entrypoints |> dict WebpackEntrypoint.encode
      ; "errors", r.errors |> list string
      ; "filteredAssets", r.filteredAssets |> int
      ; "hash", r.hash |> string
      ; "modules", r.modules |> list WebpackModule.encode
      ; "namedChunkGroups", r.namedChunkGroups |> dict WebpackEntrypoint.encode
      ; "outputPath", r.outputPath |> string
      ; "time", r.time |> int
      ; "version", r.version |> string
      ; "warnings", r.warnings |> list string
      ])
;;

let make
    assets
    assetsByChunkName
    builtAt
    children
    chunks
    entrypoints
    errors
    filteredAssets
    hash
    modules
    namedChunkGroups
    outputPath
    time
    version
    warnings
  =
  { assets
  ; assetsByChunkName
  ; builtAt
  ; children
  ; chunks
  ; entrypoints
  ; errors
  ; filteredAssets
  ; hash
  ; modules
  ; namedChunkGroups
  ; outputPath
  ; time
  ; version
  ; warnings
  }
;;

module Version = struct
  let decode json = Json.Decode.(json |> field "version" string)
  ;;

  let isSupported = Rationale.Function.Infix.(
    Js.String.split "."
    ||> Array.to_list
    ||> Utils.List.nth 0
    ||> (=) "4"
  );;
end

module FromText = struct
  exception UnsupportedVersionExn;;
  exception ParsingFailedExn;;

  let make text = Js.Promise.(
    let version =
      text
        |> Json.parseOrRaise
        |> Version.decode
        |> Version.isSupported
    in if version then
        try (
          text |> Json.parseOrRaise |> decode |> resolve
        ) with err ->
          let () = Js.log err
          in reject(ParsingFailedExn);
        else reject UnsupportedVersionExn
  );;
end

let sortByBuildTime = List.sort (fun a b -> a.builtAt - b.builtAt);;
