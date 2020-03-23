module Styles = {
  open Css;

  let root =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
    ]);
};

[@react.component]
let make = (~className="", ~children) => {
  <div className={Cn.make([className, Styles.root])}> children </div>;
};