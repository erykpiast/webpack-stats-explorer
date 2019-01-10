open Json.Decode

type t = {
  assets      : string array;
  childAssets : string Js.Dict.t;
  children    : string Js.Dict.t;
  chunks      : int array;
};;

let decode json = {
  assets      = (json |> field "assets" (array string));
  childAssets = (json |> field "childAssets" (dict string));
  children    = (json |> field "children" (dict string));
  chunks      = (json |> field "chunks" (array int));
};;
