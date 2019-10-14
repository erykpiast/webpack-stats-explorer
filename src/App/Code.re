module Styles = {
  open Css;

  let root =
    style([
      whiteSpace(`preWrap),
      wordBreak(`breakAll),
    ]);
};

let component = ReasonReact.statelessComponent("Code");

let make = (~className="", children) => {
  ...component,
  render: _self => {
    <pre className={Cn.make([className, Styles.root])}>
      {children |> ReasonReact.string}
    </pre>;
  },
};