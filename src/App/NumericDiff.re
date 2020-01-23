module Styles = {
  open Css;

  let less =
    style([
      color(Theme.Color.Removed.default),
      before([contentRule(`string("-"))]),
    ]);

  let more =
    style([color(Theme.Color.Added.default), before([contentRule(`string("+"))])]);
};

[@react.component]
let make = (~className="", ~after, ~before) => {
  let diff = after - before;
  let kindClassName =
    if (diff > 0) {
      Styles.more;
    } else {
      Styles.less;
    };

  if (diff == 0) {
    React.null;
  } else {
    <Size
      className={Cn.make([className, kindClassName])}
      value={Js.Math.abs_int(diff)}
    />;
  };
};