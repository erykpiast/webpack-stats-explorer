module Styles = {
  open Css;

  let root = style([whiteSpace(`preWrap), wordBreak(`breakAll)]);
};

let component = ReasonReact.statelessComponent("Code");

let make = (~className="", children) => {
  ...component,
  render: _self =>
    <pre className=(Cn.make([className, Styles.root]))>
      (children |> React.string)
    </pre>,
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
