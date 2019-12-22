open Rationale.Function.Infix;;

type t =
  | Added
  | Intact
  | Modified
  | Removed
;;

let toString r = (
  match r with
  | Added -> "Added"
  | Intact -> "Intact"
  | Modified -> "Modified"
  | Removed -> "Removed"
);;

let fromString s = (
  match s with
 | "Added" -> Some Added
 | "Intact" -> Some Intact
 | "Modified" -> Some Modified
 | "Removed" -> Some Removed
 | _ -> None
)

let encode = toString ||> Json.Encode.string;;
