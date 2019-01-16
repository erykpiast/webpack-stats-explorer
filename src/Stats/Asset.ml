type t = {
  emitted     : bool;
  chunkNames  : string list;
  chunks      : int list;
  name        : string;
  size        : int;
};;

let decode json = Json.Decode.({
  emitted     = (json |> field "emitted" bool);
  chunkNames  = (json |> field "chunkNames" (list string));
  chunks      = (json |> field "chunks" (list int));
  name        = (json |> field "name" string);
  size        = (json |> field "size" int);
});;

let encode r = Json.Encode.(object_ [
  ("emitted",     r.emitted |> bool);
  ("chunkNames",  r.chunkNames |> list string);
  ("chunks",      r.chunks |> list int);
  ("name",        r.name |> string);
  ("size",        r.size |> int);
]);;
