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

[@react.component]
let make = (~after, ~before) => {
  <>
    <span className=Styles.before> {React.string(before)} </span>
    <span className=Styles.after> {React.string(after)} </span>
  </>;
};