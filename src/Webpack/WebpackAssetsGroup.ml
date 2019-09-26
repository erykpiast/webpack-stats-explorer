type t =
  | Many of string list
  | Single of string;;

let decode json = Json.Decode.(
  if Js.typeof json = "string" then
    Single (string json)
  else
    Many ((list string) json)
);;

let encode r = Json.Encode.(
  match r with
  | Single s -> string s
  | Many l -> (list string) l
)