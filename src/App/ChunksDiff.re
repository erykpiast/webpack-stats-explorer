let renderFilenames = (filenames) => <>
  {ReasonReact.string(L10N.assets ++ ": ")}
  {switch (filenames) {
  | [a] => ReasonReact.string(a);
  | [_, b] => ReasonReact.string(b ++ {j|❗|j});
  }}
</>;

type props = {
  after: int,
  before: int,
  chunkname: string,
  filenames: list(string)
};

let component = ReasonReact.statelessComponent("ChunksDiff");

let make = (~title, ~chunks, _children) => {
  ...component,
  render: _self => switch (chunks) {
  | [] => ReasonReact.null
  | _ => <>
    <h3>{ReasonReact.string(title)}</h3>
    <ul>
      ...(chunks |> List.map(({ after, before, chunkname, filenames }) => {
        <li>
          <strong>{ReasonReact.string(chunkname)}</strong>
          <br/>
          <NumericDiff
            after=after
            before=before
          />
          <br/>
          {renderFilenames(filenames)}
        </li>
      }) |> Array.of_list)
    </ul>
  </>
  }
};
