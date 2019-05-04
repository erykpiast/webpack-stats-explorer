module Styles = {
  open Css;

  let list = style([listStyleType(`none), padding(px(0))]);

  let item = style([marginTop(Theme.Space.default)]);
};

let renderFilenames = filenames =>
  <>
    {ReasonReact.string(L10N.assets ++ ": ")}
    {switch (filenames) {
     | [a] => ReasonReact.string(a)
     | [_, b] => ReasonReact.string(b ++ {j|❗|j})
     | _ => ReasonReact.null
     }}
  </>;

type props = {
  after: int,
  before: int,
  chunkname: string,
  filenames: list(string),
  chunk: Compare.Chunks.chunk,
};

let component = ReasonReact.statelessComponent("ChunksDiff");

let make = (~title, ~chunks, ~onChunk, _children) => {
  ...component,
  render: _self =>
    switch (chunks) {
    | [] => ReasonReact.null
    | _ =>
      <>
        <h3> {ReasonReact.string(title)} </h3>
        <ul className=Styles.list>
          ...{
               chunks
               |> List.map(({after, before, chunk, chunkname, filenames}) =>
                    <li onClick={_ => onChunk(chunk)} className=Styles.item>
                      <strong> {ReasonReact.string(chunkname)} </strong>
                      <br />
                      <NumericDiff after before />
                      <br />
                      {renderFilenames(filenames)}
                    </li>
                  )
               |> Array.of_list
             }
        </ul>
      </>
    },
};