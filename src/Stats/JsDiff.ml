open Rationale.Function.Infix

external diffLines : string -> string -> Js.Json.t array = "diffLines"
  [@@bs.module "diff"]

module Diff = struct
  type t =
    { count : int
    ; added : bool option
    ; removed : bool option
    ; value : string
    }

  let decode json =
    Json.Decode.
      { count = json |> field "count" int
      ; added = json |> optional (field "added" bool)
      ; removed = json |> optional (field "removed" bool)
      ; value = json |> field "value" string
      }
  ;;

  let encode r =
    Json.Encode.(
      object_
        [ "count", r.count |> int
        ; "added", r.added |> nullable bool
        ; "removed", r.removed |> nullable bool
        ; "value", r.value |> string
        ])
  ;;

  let make a b = diffLines a b |> Array.map decode
end

type t =
  | Added of string
  | Removed of string
  | Intact of string

let make a b =
  Diff.make a b
  |> Array.to_list
  |> List.map
       ((fun (diff : Diff.t) ->
          ( Utils.defaultTo false diff.added
          , Utils.defaultTo false diff.removed
          , diff.value ))
       ||> fun (added, removed, value) ->
       if added = true
       then Added value
       else if removed = true
       then Removed value
       else Intact value)
;;
