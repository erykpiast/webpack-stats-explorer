module Styles = {
  open Css;

  let before =
    style([
      display(inlineBlock),
      backgroundColor(Theme.Color.Added.default),
      padding(Theme.padding),
    ]);

  let after =
    style([
      display(inlineBlock),
      backgroundColor(Theme.Color.Removed.default),
      padding(Theme.padding),
    ]);
};

let component = ReasonReact.statelessComponent("StringDiff");

let make = (_children, ~after, ~before) => {
  ...component,
  render: _self =>
    <>
      <span className=Styles.before> {ReasonReact.string(before)} </span>
      <span className=Styles.after> {ReasonReact.string(after)} </span>
    </>,
};