module Styles = {
  open Css;

  let root = style([direction(`rtl)]);
};

let ltr = {js|\u200e|js};

let component = ReasonReact.statelessComponent("ReversedText");

let make = (~className="", children) => {
  ...component,
  render: _self => {
    <span className={Cn.make([className, Styles.root])}>
      {ltr |> ReasonReact.string}
      children
      {ltr |> ReasonReact.string}
    </span>;
  },
};