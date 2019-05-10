// TODO: unify with ModulesCompare

open Compare.Chunks;
open Compare.Kind;
open State.NavigationPath;

let component = ReasonReact.statelessComponent("ChunksCompare");

let mapChunksToProps = (chunks, onChunk) => {
  let added =
    chunks.added
    |> List.map((chunk: Summary.t) =>
         ChunksDiff.{
           after: chunk.size,
           before: 0,
           chunkname: chunk.name,
           filenames: [chunk.filename],
           chunk: Summary(chunk),
           onChunk: chunk => onChunk(Segment.of_chunk(Added, chunk)),
         }
       );
  let removed =
    chunks.removed
    |> List.map((chunk: Summary.t) =>
         ChunksDiff.{
           after: 0,
           before: chunk.size,
           chunkname: chunk.name,
           filenames: [chunk.filename],
           chunk: Summary(chunk),
           onChunk: chunk => onChunk(Segment.of_chunk(Removed, chunk)),
         }
       );
  let intact =
    chunks.intact
    |> List.map((chunk: Summary.t) =>
         ChunksDiff.{
           after: chunk.size,
           before: chunk.size,
           chunkname: chunk.name,
           filenames: [chunk.filename],
           chunk: Summary(chunk),
           onChunk: chunk => onChunk(Segment.of_chunk(Intact, chunk)),
         }
       );
  let modified =
    chunks.modified
    |> List.map((chunk: ModifiedSummary.t) =>
         ChunksDiff.{
           after: snd(chunk.size),
           before: fst(chunk.size),
           chunkname: chunk.name,
           filenames: [fst(chunk.filename), snd(chunk.filename)],
           chunk: ModifiedSummary(chunk),
           onChunk: chunk => onChunk(Segment.of_chunk(Modified, chunk)),
         }
       );

  // TODO: test
  Belt.List.concatMany([|added, modified, removed, intact|])
  |> List.sort(
       ChunksDiff.(
         (a, b) => {
           let aDiff = a.after - a.before;
           let bDiff = b.after - b.before;
           let diffOfDiffs = bDiff - aDiff;

           if (diffOfDiffs === 0) {
             0;
           } else if (aDiff === 0) {
             1;
           } else if (bDiff === 0) {
             (-1);
           } else {
             diffOfDiffs;
           };
         }
       ),
     );
};

let make = (~chunks, ~onChunk, _children) => {
  ...component,
  render: _self => <ChunksDiff chunks={mapChunksToProps(chunks, onChunk)} />,
};