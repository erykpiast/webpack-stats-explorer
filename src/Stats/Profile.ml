open Json.Decode

type t = {
  building     : int;
  dependencies : int option;
  factory      : int;
};;

let decode json = {
  building     = (json |> field "building" int);
  dependencies = (json |> field "dependencies" (optional int));
  factory      = (json |> field "factory" int);
};;
