let getChunkName = (chunk: Chunk.t) => switch (chunk.names) {
| [] => List.nth(chunk.files, 0);
| [name, ..._] => name
};

let getFilename = (chunk: Chunk.t) => List.nth(chunk.files, 0);

let renderChunksDiff = (mapper, title, chunks) => <ChunksDiff
  chunks=(chunks |> List.map(mapper))
  title=title
/>;

let component = ReasonReact.statelessComponent("Compare");

let make = (~size, ~chunks: Diff.t(Chunk.t), _children) => {
  ...component,
  render: _self => {
    let added = renderChunksDiff((chunk: Chunk.t) => {
      after: chunk.size,
      before: 0,
      chunkname: getChunkName(chunk),
      filenames: [getFilename(chunk)]
    }, L10N.added, chunks.added);
    let removed = renderChunksDiff((chunk: Chunk.t) => {
      after: 0,
      before: chunk.size,
      chunkname: getChunkName(chunk),
      filenames: [getFilename(chunk)]
    }, L10N.removed, chunks.removed);
    let intact = renderChunksDiff((chunk: Chunk.t) => {
      after: chunk.size,
      before: chunk.size,
      chunkname: getChunkName(chunk),
      filenames: [getFilename(chunk)]
    }, L10N.intact, chunks.intact);
    let modified = renderChunksDiff(((a: Chunk.t, b: Chunk.t)) => {
      after: b.size,
      before: a.size,
      chunkname: getChunkName(a),
      filenames: [a, b] |> List.map(getFilename)
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