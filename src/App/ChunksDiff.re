// TODO: unify with ModulesDiff

module Styles = {
  open Css;

  let list =
    style([listStyleType(`none), padding(px(0)), margin(px(0))]);

  let item =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      marginBottom(Theme.Space.double),
      marginTop(Theme.Space.double),
    ]);

  let size =
    style([
      marginLeft(`auto),
      marginRight(Theme.Space.default),
      color(Theme.Color.Text.secondary),
    ]);
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
  onChunk: Compare.Chunks.chunk => unit,
};

let component = ReasonReact.statelessComponent("ChunksDiff");

let make = (~chunks, _children) => {
  ...component,
  render: _self =>
    switch (chunks) {
    | [] => ReasonReact.null
    | _ =>
      <ul className=Styles.list>
        ...{
             chunks
             |> List.map(
                  ({after, before, chunk, onChunk, chunkname, filenames}) =>
                  <li onClick={_ => onChunk(chunk)} className=Styles.item>
                    <strong> {ReasonReact.string(chunkname)} </strong>
                    {before !== 0
                       ? <Size className=Styles.size value=before />
                       : ReasonReact.null}
                    <NumericDiff after before />
                  </li>
                )
             |> Array.of_list
           }
      </ul>
    },
};