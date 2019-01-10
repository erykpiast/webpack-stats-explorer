open Json.Decode

type t = {
  emitted     : bool;
  chunkNames  : string array;
  chunks      : int array;
  name        : string;
  size        : int;
};;

let decode json = {
  emitted     = (json |> field "emitted" bool);
  chunkNames  = (json |> field "chunkNames" (array string));
  chunks      = (json |> field "chunks" (array int));
  name        = (json |> field "name" string);
  size        = (json |> field "size" int);
};;
