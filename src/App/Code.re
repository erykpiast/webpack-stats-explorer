module Styles = {
  open Css;

  let root = style([whiteSpace(`preWrap), wordBreak(`breakAll)]);
};

[@react.component]
let make = (~className="", ~children) => {
  <pre className={Cn.make([className, Styles.root])}>
    {children |> React.string}
  </pre>;
};