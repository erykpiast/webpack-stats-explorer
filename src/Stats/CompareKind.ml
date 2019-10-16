type t =
  | Added
  | Intact
  | Modified
  | Removed
;;

let encode r = (
  match r with
  | Added -> "Added"
  | Intact -> "Intact"
  | Modified -> "Modified"
  | Removed -> "Removed"
) |> Json.Encode.string
;;