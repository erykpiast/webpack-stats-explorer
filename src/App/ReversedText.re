module Styles = {
  open Css;

  let root = style([direction(`rtl)]);
};

let ltr = {js|\u200e|js};

let component = ReasonReact.statelessComponent("ReversedText");

let make = (~className="", children) => {
  ...component,
  render: _self =>
    <span className=(Cn.make([className, Styles.root]))>
      (ltr |> React.string)
      children
      (ltr |> React.string)
    </span>,
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component,
    (
      reactProps: {
        .
        "className": option('className),
        "children": 'children,
      },
    ) =>
    make(~className=?reactProps##className, reactProps##children)
  );
[@bs.obj]
external makeProps:
  (~children: 'children, ~className: 'className=?, unit) =>
  {
    .
    "className": option('className),
    "children": 'children,
  } =
  "";
