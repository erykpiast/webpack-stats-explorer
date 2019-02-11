open Compare.Chunks;

let renderChunksDiff = (mapper, title, chunks) => <ChunksDiff
  chunks=(chunks |> List.map(mapper))
  title=title
/>;

let component = ReasonReact.statelessComponent("Compare");

let make = (~size, ~chunks: t, _children) => {
  ...component,
  render: _self => {
    let added = renderChunksDiff((chunk: Summary.t) => {
      after: chunk.size,
      before: 0,
      chunkname: chunk.name,
      filenames: [chunk.filename]
    }, L10N.added, chunks.added);
    let removed = renderChunksDiff((chunk: Summary.t) => {
      after: 0,
      before: chunk.size,
      chunkname: chunk.name,
      filenames: [chunk.filename]
    }, L10N.removed, chunks.removed);
    let intact = renderChunksDiff((chunk: Summary.t) => {
      after: chunk.size,
      before: chunk.size,
      chunkname: chunk.name,
      filenames: [chunk.filename]
    }, L10N.intact, chunks.intact);
    let modified = renderChunksDiff((chunk: ModifiedSummary.t) => {
      after: snd(chunk.size),
      before: fst(chunk.size),
      chunkname: chunk.name,
      filenames: [fst(chunk.filename), snd(chunk.filename)]
    }, L10N.modified, chunks.modified);

    <>
      {ReasonReact.string(L10N.overalSize ++ " ")}
      <NumericDiff
        after={snd(size)}
        before={fst(size)}
      />
      <h2>{ReasonReact.string(L10N.chunks)}</h2>
      {added}
      {removed}
      {intact}
      {modified}
    </>
  }
};