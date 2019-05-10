// TODO: unify with ChunksDiff

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
  name: string,
  module_: Compare.Modules.module_,
  onModule: Compare.Modules.module_ => unit,
};

let component = ReasonReact.statelessComponent("ModulesDiff");

let make = (~modules, ~className="", _children) => {
  ...component,
  render: _self =>
    switch (modules) {
    | [] => ReasonReact.null
    | _ =>
      <ul className={Cn.make([Styles.list, className])}>
        ...{
             modules
             |> List.map(({after, before, module_, name, onModule}) =>
                  <li onClick={_ => onModule(module_)} className=Styles.item>
                    <strong> {ReasonReact.string(name)} </strong>
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