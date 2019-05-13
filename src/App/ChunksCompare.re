// TODO: unify with ModulesCompare

open Compare.Chunks;
open Compare.Kind;
open State.NavigationPath;

let component = ReasonReact.statelessComponent("ChunksCompare");

let mapChunksToProps = (chunks, onChunk) => {
  let added =
    chunks.added
    |> List.map((chunk: Summary.t) =>
         (
           {
             after: chunk.size,
             before: 0,
             name: chunk.name,
             value: Summary(chunk),
             onChange: chunk => onChunk(Segment.of_chunk(Added, chunk)),
           }: ChunksDiff.props
         )
       );
  let removed =
    chunks.removed
    |> List.map((chunk: Summary.t) =>
         (
           {
             after: 0,
             before: chunk.size,
             name: chunk.name,
             value: Summary(chunk),
             onChange: chunk => onChunk(Segment.of_chunk(Removed, chunk)),
           }: ChunksDiff.props
         )
       );
  let intact =
    chunks.intact
    |> List.map((chunk: Summary.t) =>
         (
           {
             after: chunk.size,
             before: chunk.size,
             name: chunk.name,
             value: Summary(chunk),
             onChange: chunk => onChunk(Segment.of_chunk(Intact, chunk)),
           }: ChunksDiff.props
         )
       );
  let modified =
    chunks.modified
    |> List.map((chunk: ModifiedSummary.t) =>
         (
           {
             after: snd(chunk.size),
             before: fst(chunk.size),
             name: chunk.name,
             value: ModifiedSummary(chunk),
             onChange: chunk => onChunk(Segment.of_chunk(Modified, chunk)),
           }: ChunksDiff.props
         )
       );

  // TODO: test
  Belt.List.concatMany([|added, modified, removed, intact|])
  |> List.sort((a: ChunksDiff.props, b: ChunksDiff.props) => {
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
     });
};

let make = (~chunks, ~onChunk, _children) => {
  ...component,
  render: _self => <ChunksDiff data={mapChunksToProps(chunks, onChunk)} />,
};