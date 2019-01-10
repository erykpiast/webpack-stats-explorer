open Json.Decode

type t = {
  childrenByOrder : string Js.Dict.t;
  entry           : bool;
  files           : string array;
  filteredModules : int;
  hash            : string;
  id              : int;
  initial         : bool;
  modules         : Module.t array;
  names           : string array;
  origins         : Origin.t array;
  parents         : string array;
  rendered        : bool;
  siblings        : string array;
  size            : int;
};;

let decode json = {
  childrenByOrder = (json |> field "childrenByOrder" (dict string));
  entry           = (json |> field "entry" bool);
  files           = (json |> field "files" (array string));
  filteredModules = (json |> field "filteredModules" int);
  hash            = (json |> field "hash" string);
  id              = (json |> field "id" int);
  initial         = (json |> field "initial" bool);
  modules         = (json |> field "modules" (array Module.decode));
  names           = (json |> field "names" (array string));
  origins         = (json |> field "origins" (array Origin.decode));
  parents         = (json |> field "parents" (array string));
  rendered        = (json |> field "rendered" bool);
  siblings        = (json |> field "siblings" (array string));
  size            = (json |> field "size" int);
};;
