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
  render: _self => {
    <div className={Cn.make([className, Styles.root])}> ...children </div>;
  },
};