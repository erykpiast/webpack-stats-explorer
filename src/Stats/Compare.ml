type t = {
  chunks  : Chunk.t Diff.t;
  size    : int * int;
};;

let calcSize = List.fold_left (fun acc (a: Chunk.t) -> a.size + acc) 0;;

let chunksSimilar (a: Chunk.t) (b: Chunk.t) =
  (Utils.List.isEqual a.files b.files) ||
  ((Utils.List.isEqual a.names b.names) && ((List.length a.names) != 0))

let diffChunks = Diff.create chunksSimilar Chunk.eql;;

let compare (a : Stats.t) (b : Stats.t) = {
  chunks = diffChunks a.chunks b.chunks;
  size   = (calcSize a.chunks, calcSize b.chunks);
};;

let encode r = Json.Encode.(object_ [
  ("chunks", r.chunks |> Diff.encode Chunk.encode);
  ("size",   r.size |> tuple2 int int);
]);;
