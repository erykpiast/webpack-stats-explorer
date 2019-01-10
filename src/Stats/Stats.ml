open Json.Decode

type compilation_error = string
type compilation_warning = string

type t = {
  assets            : Asset.t array;
  assetsByChunkName : string Js.Dict.t;
  builtAt           : int;
  children          : string array;
  chunks            : Chunk.t array;
  entrypoints       : Entrypoint.t Js.Dict.t;
  errors            : string array;
  filteredAssets    : int;
  hash              : string;
  modules           : Module.t array;
  namedChunkGroups  : Entrypoint.t Js.Dict.t;
  outputPath        : string;
  time              : int;
  version           : string;
  warnings          : string array;
};;

let decode json = {
  assets            = (json |> field "assets" (array Asset.decode));
  assetsByChunkName = (json |> field "assetsByChunkName" (dict string));
  builtAt           = (json |> field "builtAt" int);
  children          = (json |> field "children" (array string));
  chunks            = (json |> field "chunks" (array Chunk.decode));
  entrypoints       = (json |> field "entrypoints" (dict Entrypoint.decode));
  errors            = (json |> field "errors" (array string));
  filteredAssets    = (json |> field "filteredAssets" int);
  hash              = (json |> field "hash" string);
  modules           = (json |> field "modules" (array Module.decode));
  namedChunkGroups  = (json |> field "namedChunkGroups" (dict Entrypoint.decode));
  outputPath        = (json |> field "outputPath" string);
  time              = (json |> field "time" int);
  version           = (json |> field "version" string);
  warnings          = (json |> field "warnings" (array string));
};;
