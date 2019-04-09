module Styles = {
  open Css;

  let better =
    style([
      display(inlineBlock),
      backgroundColor(Theme.betterColor),
      padding(Theme.padding),
      before([contentRule("-")]),
    ]);

  let worse =
    style([
      display(inlineBlock),
      backgroundColor(Theme.worseColor),
      padding(Theme.padding),
      before([contentRule("+")]),
    ]);
};

let component = ReasonReact.statelessComponent("NumericDiff");

let make = (_children, ~after, ~before) => {
  ...component,
  render: _self => {
    let diff = after - before;
    let className =
      if (diff > 0) {
        Styles.worse;
      } else {
        Styles.better;
      };

    <span>
      <Size value=after />
      {ReasonReact.string(" ")}
      {diff != 0
         ? <Size className value={Js.Math.abs_int(diff)} /> : ReasonReact.null}
    </span>;
  },
};