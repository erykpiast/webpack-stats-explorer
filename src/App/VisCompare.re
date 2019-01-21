let getChunkName = (chunk: Chunk.t) => switch(chunk.names) {
| [] => List.nth(chunk.files, 0);
| [name, ..._] => name
}

let displayModifiedChunks = (chunks) => chunks
  |> Array.of_list
  |> Array.map((chunk: (Chunk.t, Chunk.t)) => <li>
      <NumericDiff
        after=snd(chunk).size
        before=fst(chunk).size
        label=getChunkName(fst(chunk))
        unit=NumericDiff.KB
      />
    </li>);

let displayAddedChunks = (chunks) => chunks
  |> Array.of_list
  |> Array.map((chunk: Chunk.t) => <li>
      <NumericDiff
        after=chunk.size
        before=0
        label=getChunkName(chunk)
        unit=NumericDiff.KB
      />
    </li>);

let displayRemovedChunks = (chunks) => chunks
  |> Array.of_list
  |> Array.map((chunk: Chunk.t) => <li>
      <NumericDiff
        after=0
        before=chunk.size
        label=getChunkName(chunk)
        unit=NumericDiff.KB
      />
    </li>);

let component = ReasonReact.statelessComponent("Compare");

let make = (~size, ~chunks: Diff.t(Chunk.t), _children) => {
  ...component,
  render: _self => {
    <>
      <NumericDiff
        after={snd(size)}
        before={fst(size)}
        label="Overal size"
        unit=NumericDiff.KB
      />
      <h2>{ReasonReact.string("Chunks")}</h2>
      <h3>{ReasonReact.string("Added")}</h3>
      <ul>
        ...(displayAddedChunks(chunks.added))
      </ul>
      <h3>{ReasonReact.string("Modified")}</h3>
      <ul>
        ...(displayModifiedChunks(chunks.modified))
      </ul>
      <h3>{ReasonReact.string("Removed")}</h3>
      <ul>
        ...(displayRemovedChunks(chunks.removed))
      </ul>
    </>;
  },
};