module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      height(`percent(100.0)),
      width(`percent(100.0)),
    ]);

  let side =
    style([
      display(block),
      width(`percent(25.0)),
      borderRight(px(1), `solid, Theme.Color.Border.default),
      padding(Theme.Space.default),
    ]);

  let main =
    style([
      display(block),
      width(`percent(75.0)),
      padding(Theme.Space.default),
    ]);
};

let component = ReasonReact.statelessComponent("NavigationLayout");

let make = (~side, ~main, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.wrapper>
      <div className=Styles.side> side </div>
      <div className=Styles.main> main </div>
    </div>,
};