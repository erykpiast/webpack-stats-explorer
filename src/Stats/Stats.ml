type compilation_error = string
type compilation_warning = string

type t = {
  assets            : Asset.t list;
  assetsByChunkName : string Js.Dict.t;
  builtAt           : int;
  children          : string list;
  chunks            : Chunk.t list;
  entrypoints       : Entrypoint.t Js.Dict.t;
  errors            : string list;
  filteredAssets    : int;
  hash              : string;
  modules           : Module.t list;
  namedChunkGroups  : Entrypoint.t Js.Dict.t;
  outputPath        : string;
  time              : int;
  version           : string;
  warnings          : string list;
};;

let decode json = Json.Decode.({
  assets            = (json |> field "assets" (list Asset.decode));
  assetsByChunkName = (json |> field "assetsByChunkName" (dict string));
  builtAt           = (json |> field "builtAt" int);
  children          = (json |> field "children" (list string));
  chunks            = (json |> field "chunks" (list Chunk.decode));
  entrypoints       = (json |> field "entrypoints" (dict Entrypoint.decode));
  errors            = (json |> field "errors" (list string));
  filteredAssets    = (json |> field "filteredAssets" int);
  hash              = (json |> field "hash" string);
  modules           = (json |> field "modules" (list Module.decode));
  namedChunkGroups  = (json |> field "namedChunkGroups" (dict Entrypoint.decode));
  outputPath        = (json |> field "outputPath" string);
  time              = (json |> field "time" int);
  version           = (json |> field "version" string);
  warnings          = (json |> field "warnings" (list string));
});;

let encode r = Json.Encode.(object_ [
  ("assets",            r.assets |> list Asset.encode);
  ("assetsByChunkName", r.assetsByChunkName |> Js.Dict.map (fun [@bs] x -> x |> string) |> dict);
  ("builtAt",           r.builtAt |> int);
  ("children",          r.children |> list string);
  ("chunks",            r.chunks |> list Chunk.encode);
  ("entrypoints",       r.entrypoints |> Js.Dict.map (fun [@bs] x -> x |> Entrypoint.encode) |> dict);
  ("errors",            r.errors |> list string);
  ("filteredAssets",    r.filteredAssets |> int);
  ("hash",              r.hash |> string);
  ("modules",           r.modules |> list Module.encode);
  ("namedChunkGroups",  r.namedChunkGroups |> Js.Dict.map (fun [@bs] x -> x |> Entrypoint.encode) |> dict);
  ("outputPath",        r.outputPath |> string);
  ("time",              r.time |> int);
  ("version",           r.version |> string);
  ("warnings",          r.warnings |> list string);
]);;