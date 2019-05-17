
type compilation_error = string
type compilation_warning = string

type t =
  { assets : Asset.t list
  ; assetsByChunkName : string Js.Dict.t
  ; children : t list
  ; chunks : Chunk.t list
  ; entrypoints : Entrypoint.t Js.Dict.t
  ; errors : string list
  ; filteredAssets : int
  ; modules : Module.t list
  ; name : string
  ; namedChunkGroups : Entrypoint.t Js.Dict.t
  ; outputPath : string
  ; publicPath: string
  ; warnings : string list
  }

let rec decode json =
  Json.Decode.
    { assets = json |> field "assets" (list Asset.decode)
    ; assetsByChunkName = json |> field "assetsByChunkName" (dict string)
    ; children = json |> field "children" (list decode)
    ; chunks = json |> field "chunks" (list Chunk.decode)
    ; entrypoints = json |> field "entrypoints" (dict Entrypoint.decode)
    ; errors = json |> field "errors" (list string)
    ; filteredAssets = json |> field "filteredAssets" int
    ; modules = json |> field "modules" (list Module.decode)
    ; name = json |> field "name" string
    ; namedChunkGroups = json |> field "namedChunkGroups" (dict Entrypoint.decode)
    ; outputPath = json |> field "outputPath" string
    ; publicPath = json |> field "publicPath" string
    ; warnings = json |> field "warnings" (list string)
    }
;;

let rec encode r =
  Json.Encode.(
    object_
      [ "assets", r.assets |> list Asset.encode
      ; ( "assetsByChunkName"
        , r.assetsByChunkName |> Js.Dict.map (fun [@bs] x -> x |> string) |> dict )
      ; "children", r.children |> list encode
      ; "chunks", r.chunks |> list Chunk.encode
      ; ( "entrypoints"
        , r.entrypoints |> Js.Dict.map (fun [@bs] x -> x |> Entrypoint.encode) |> dict )
      ; "errors", r.errors |> list string
      ; "filteredAssets", r.filteredAssets |> int
      ; "modules", r.modules |> list Module.encode
      ; "name", r.name |> string
      ; ( "namedChunkGroups"
        , r.namedChunkGroups
          |> Js.Dict.map (fun [@bs] x -> x |> Entrypoint.encode)
          |> dict )
      ; "outputPath", r.outputPath |> string
      ; "publicPath", r.publicPath |> string
      ; "warnings", r.warnings |> list string
      ])
;;