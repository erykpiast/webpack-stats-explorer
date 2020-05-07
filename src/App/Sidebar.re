module Styles = {
  open Css;

  let root =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
    ]);

  let scrollable =
    style([
      overflowY(`auto),
      minHeight(px(0)),
      flexGrow(0.0),
    ]);

  let fixed = style([marginBottom(px(0)), marginTop(`auto), flexShrink(0.0), flexGrow(0.0)]);
};

[@react.component]
let make = (~className="", ~fixed, ~scrollable) => {
  <div className={Cn.make([className, Styles.root])}>
    <div className=Styles.scrollable> scrollable </div>
    <div className=Styles.fixed> fixed </div>
  </div>;
};