module Styles = {
  open Css;

  let less =
    style([
      color(Theme.Color.Removed.default),
      before([contentRule("-")]),
    ]);

  let more =
    style([color(Theme.Color.Added.default), before([contentRule("+")])]);
};

let component = ReasonReact.statelessComponent("NumericDiff");

let make = (~className="", ~after, ~before, _children) => {
  ...component,
  render: _self => {
    let diff = after - before;
    let kindClassName =
      if (diff > 0) {
        Styles.more;
      } else {
        Styles.less;
      };

    if (diff == 0) {
      ReasonReact.null;
    } else {
      <Size
        className={kindClassName ++ " " ++ className}
        value={Js.Math.abs_int(diff)}
      />;
    };
  },
};