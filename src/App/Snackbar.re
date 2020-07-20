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

[@react.component]
let make = (~className="", ~children) => {
  <div className={Cn.fromList([className, Styles.root])}> children </div>;
};
