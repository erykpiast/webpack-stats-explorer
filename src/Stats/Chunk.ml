type t = {
  childrenByOrder : string Js.Dict.t;
  entry           : bool;
  files           : string list;
  filteredModules : int;
  hash            : string;
  id              : int;
  initial         : bool;
  modules         : Module.t list;
  names           : string list;
  origins         : Origin.t list;
  parents         : int list;
  rendered        : bool;
  siblings        : int list;
  size            : int;
};;

let decode json = Json.Decode.({
  childrenByOrder = (json |> field "childrenByOrder" (dict string));
  entry           = (json |> field "entry" bool);
  files           = (json |> field "files" (list string));
  filteredModules = (json |> field "filteredModules" int);
  hash            = (json |> field "hash" string);
  id              = (json |> field "id" int);
  initial         = (json |> field "initial" bool);
  modules         = (json |> field "modules" (list Module.decode));
  names           = (json |> field "names" (list string));
  origins         = (json |> field "origins" (list Origin.decode));
  parents         = (json |> field "parents" (list int));
  rendered        = (json |> field "rendered" bool);
  siblings        = (json |> field "siblings" (list int));
  size            = (json |> field "size" int);
});;

let encode r = Json.Encode.(object_ [
  ("childrenByOrder", r.childrenByOrder |> Js.Dict.map (fun [@bs] x -> x |> string) |> dict);
  ("entry",           r.entry |> bool);
  ("files",           r.files |> list string);
  ("filteredModules", r.filteredModules |> int);
  ("hash",            r.hash |> string);
  ("id",              r.id |> int);
  ("initial",         r.initial |> bool);
  ("modules",         r.modules |> list Module.encode);
  ("names",           r.names |> list string);
  ("origins",         r.origins |> list Origin.encode);
  ("parents",         r.parents |> list int);
  ("rendered",        r.rendered |> bool);
  ("siblings",        r.siblings |> list int);
  ("size",            r.size |> int);
]);;

let make
  childrenByOrder
  entry
  files
  filteredModules
  hash
  id
  initial
  modules
  names
  origins
  parents
  rendered
  siblings
  size
= {
  childrenByOrder = childrenByOrder;
  entry           = entry;
  files           = files;
  filteredModules = filteredModules;
  hash            = hash;
  id              = id;
  initial         = initial;
  modules         = modules;
  names           = names;
  origins         = origins;
  parents         = parents;
  rendered        = rendered;
  siblings        = siblings;
  size            = size;
};;

let eql a b = a.size = b.size &&
  (Utils.List.isEqual a.names b.names) &&
  (Utils.List.isEqual a.files b.files)
;;
