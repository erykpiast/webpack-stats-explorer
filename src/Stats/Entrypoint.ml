type t =
  { assets : string list
  ; childAssets : string Js.Dict.t
  ; children : string Js.Dict.t
  ; chunks : int list
  }

let decode json =
  Json.Decode.
    { assets = json |> field "assets" (list string)
    ; childAssets = json |> field "childAssets" (dict string)
    ; children = json |> field "children" (dict string)
    ; chunks = json |> field "chunks" (list int)
    }
;;

let encode r =
  Json.Encode.(
    object_
      [ "assets", r.assets |> list string
      ; "childAssets", r.childAssets |> Js.Dict.map (fun [@bs] x -> x |> string) |> dict
      ; "children", r.children |> Js.Dict.map (fun [@bs] x -> x |> string) |> dict
      ; "chunks", r.chunks |> list int
      ])
;;
