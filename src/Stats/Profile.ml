type t = {
  building     : int;
  dependencies : int option;
  factory      : int;
};;

let decode json = Json.Decode.({
  building     = (json |> field "building" int);
  dependencies = (json |> field "dependencies" (optional int));
  factory      = (json |> field "factory" int);
});;

let encode r = Json.Encode.(object_ [
  ("building",      r.building |> int);
  ("dependencies",  r.dependencies |> nullable int);
  ("factory",       r.factory |> int);
]);;