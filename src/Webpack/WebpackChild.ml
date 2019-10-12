
type compilation_error = string
type compilation_warning = string

type t =
  { assets : WebpackAsset.t list
  ; assetsByChunkName : string Js.Dict.t
  ; children : t list
  ; chunks : WebpackChunk.t list
  ; entrypoints : WebpackEntrypoint.t Js.Dict.t
  ; errors : string list
  ; filteredAssets : int
  ; modules : WebpackModule.t list
  ; name : string
  ; namedChunkGroups : WebpackEntrypoint.t Js.Dict.t
  ; outputPath : string
  ; publicPath: string
  ; warnings : string list
  }

let rec decode json =
  Json.Decode.
    { assets = json |> field "assets" (list WebpackAsset.decode)
    ; assetsByChunkName = json |> field "assetsByChunkName" (dict string)
    ; children = json |> field "children" (list decode)
    ; chunks = json |> field "chunks" (list WebpackChunk.decode)
    ; entrypoints = json |> field "entrypoints" (dict WebpackEntrypoint.decode)
    ; errors = json |> field "errors" (list string)
    ; filteredAssets = json |> field "filteredAssets" int
    ; modules = json |> field "modules" (list WebpackModule.decode)
    ; name = json |> field "name" string
    ; namedChunkGroups = json |> field "namedChunkGroups" (dict WebpackEntrypoint.decode)
    ; outputPath = json |> field "outputPath" string
    ; publicPath = json |> field "publicPath" string
    ; warnings = json |> field "warnings" (list string)
    }
;;

let rec encode r =
  Json.Encode.(
    object_
      [ "assets", r.assets |> list WebpackAsset.encode
      ; "assetsByChunkName", r.assetsByChunkName |> dict string
      ; "children", r.children |> list encode
      ; "chunks", r.chunks |> list WebpackChunk.encode
      ; "entrypoints", r.entrypoints |> dict WebpackEntrypoint.encode
      ; "errors", r.errors |> list string
      ; "filteredAssets", r.filteredAssets |> int
      ; "modules", r.modules |> list WebpackModule.encode
      ; "name", r.name |> string
      ; "namedChunkGroups", r.namedChunkGroups |> dict WebpackEntrypoint.encode
      ; "outputPath", r.outputPath |> string
      ; "publicPath", r.publicPath |> string
      ; "warnings", r.warnings |> list string
      ])
;;