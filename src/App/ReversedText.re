module Styles = {
  open Css;

  let root = style([direction(`rtl)]);
};

let ltr = {js|\u200e|js};

[@react.component]
let make = (~className="", ~children) => {
  <span className={Cn.fromList([className, Styles.root])}>
    {ltr |> React.string}
    children
    {ltr |> React.string}
  </span>;
};
