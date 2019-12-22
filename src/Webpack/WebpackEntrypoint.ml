type t =
  { assets : string list
  ; childAssets : string Js.Dict.t
  ; children : string Js.Dict.t
  ; chunks : string list
  }

let decode json =
  Json.Decode.
    { assets = json |> field "assets" (list string)
    ; childAssets = json |> field "childAssets" (dict string)
    ; children = json |> field "children" (dict string)
    ; chunks = json |> field "chunks" (list Utils.Json.Decode.forceString)
    }
;;

let encode r =
  Json.Encode.(
    object_
      [ "assets", r.assets |> list string
      ; "childAssets", r.childAssets |> dict string
      ; "children", r.children |> dict string
      ; "chunks", r.chunks |> list string
      ])
;;
