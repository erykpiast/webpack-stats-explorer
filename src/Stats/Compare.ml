type t = {
  chunks : Chunk.t Diff.t;
};;

let diffChunks = Diff.create (fun (a: Chunk.t) (b: Chunk.t) -> (Utils.List.isEqual a.names b.names));;

let compare (a : Stats.t) (b : Stats.t) = {
  chunks = (diffChunks a.chunks b.chunks);
};;

let encode r = Json.Encode.(object_ [
  ("chunks", r.chunks |> Diff.encode Chunk.encode)
]);;
