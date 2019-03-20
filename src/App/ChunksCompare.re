open Compare.Chunks;

let component = ReasonReact.statelessComponent("ChunksCompare");

let make = (~size, ~chunks: t, ~onChunk, _children) => {
  let renderChunksDiff = (mapper, title, onChunk, chunks) => <ChunksDiff
    chunks=(chunks |> List.map(mapper))
    title=title
    onChunk=onChunk
  />;
  {
    ...component,
    render: _self => {
      let added = renderChunksDiff(
        (chunk: Summary.t) => {
          after: chunk.size,
          before: 0,
          chunkname: chunk.name,
          filenames: [chunk.filename],
          chunk: Summary(chunk)
        },
        L10N.added,
        (chunk) => onChunk(State.NavigationPath.Added(State.Chunk(chunk))), chunks.added);
      let removed = renderChunksDiff(
        (chunk: Summary.t) => {
          after: 0,
          before: chunk.size,
          chunkname: chunk.name,
          filenames: [chunk.filename],
          chunk: Summary(chunk)
        },
        L10N.removed,
        (chunk) => onChunk(State.NavigationPath.Removed(State.Chunk(chunk))), chunks.removed);
      let intact = renderChunksDiff(
        (chunk: Summary.t) => {
          after: chunk.size,
          before: chunk.size,
          chunkname: chunk.name,
          filenames: [chunk.filename],
          chunk: Summary(chunk)
        },
        L10N.intact,
        (chunk) => onChunk(State.NavigationPath.Intact(State.Chunk(chunk))), chunks.intact);
      let modified = renderChunksDiff(
        (chunk: ModifiedSummary.t) => {
          after: snd(chunk.size),
          before: fst(chunk.size),
          chunkname: chunk.name,
          filenames: [fst(chunk.filename), snd(chunk.filename)],
          chunk: ModifiedSummary(chunk)
        },
        L10N.modified,
        (chunk) => onChunk(State.NavigationPath.Modified(State.Chunk(chunk))), chunks.modified);
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
};