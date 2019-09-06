type compilation_error = string
type compilation_warning = string

type t =
  { assets : Asset.t list
  ; assetsByChunkName : AssetsGroup.t Js.Dict.t
  ; builtAt : int
  ; children : Child.t list
  ; chunks : Chunk.t list
  ; entrypoints : Entrypoint.t Js.Dict.t
  ; errors : string list
  ; filteredAssets : int
  ; hash : string
  ; modules : Module.t list
  ; namedChunkGroups : Entrypoint.t Js.Dict.t
  ; outputPath : string
  ; time : int
  ; version : string
  ; warnings : string list
  }

let decode json =
  Json.Decode.
    { assets = json |> field "assets" (list Asset.decode)
    ; assetsByChunkName = json |> field "assetsByChunkName" (dict AssetsGroup.decode)
    ; builtAt = json |> field "builtAt" int
    ; children = json |> field "children" (list Child.decode)
    ; chunks = json |> field "chunks" (list Chunk.decode)
    ; entrypoints = json |> field "entrypoints" (dict Entrypoint.decode)
    ; errors = json |> field "errors" (list string)
    ; filteredAssets = json |> field "filteredAssets" int
    ; hash = json |> field "hash" string
    ; modules = json |> field "modules" (list Module.decode)
    ; namedChunkGroups = json |> field "namedChunkGroups" (dict Entrypoint.decode)
    ; outputPath = json |> field "outputPath" string
    ; time = json |> field "time" int
    ; version = json |> field "version" string
    ; warnings = json |> field "warnings" (list string)
    }
;;

let encode r =
  Json.Encode.(
    object_
      [ "assets", r.assets |> list Asset.encode
      ; "assetsByChunkName", r.assetsByChunkName |> dict AssetsGroup.encode
      ; "builtAt", r.builtAt |> int
      ; "children", r.children |> list Child.encode
      ; "chunks", r.chunks |> list Chunk.encode
      ; "entrypoints", r.entrypoints |> dict Entrypoint.encode
      ; "errors", r.errors |> list string
      ; "filteredAssets", r.filteredAssets |> int
      ; "hash", r.hash |> string
      ; "modules", r.modules |> list Module.encode
      ; "namedChunkGroups", r.namedChunkGroups |> dict Entrypoint.encode
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
end;;
