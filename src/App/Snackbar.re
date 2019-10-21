module Styles = {
  open Css;

  let root =
    style([
      left(`percent(50.0)),
      transform(translateX(`percent(-50.0))),
      bottom(Theme.Space.triple),
      display(`flex),
      zIndex(1400),
      position(fixed),
      alignItems(center),
      justifyContent(center),
      borderRadius(Theme.Space.half),
      padding(Theme.Space.double),
      color(Theme.Color.Text.contrast),
      backgroundColor(Theme.Color.Background.dark),
    ]);
};

let component = ReasonReact.statelessComponent("Snackbar");

let make = (~className="", children) => {
  ...component,
  render: _self =>
    <div className={Cn.make([className, Styles.root])}> children </div>,
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