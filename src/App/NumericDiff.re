module Styles = {
  open Css;

  let less =
    style([
      color(Theme.Color.Removed.default),
      before([contentRule("-")]),
    ]);

  let more =
    style([color(Theme.Color.Added.default), before([contentRule("+")])]);
};

let component = ReasonReact.statelessComponent("NumericDiff");

let make = (~className="", ~after, ~before) => {
  ...component,
  render: _self => {
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
  },
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
        "before": 'before,
        "after": 'after,
        "className": option('className),
      },
    ) =>
    make(
      ~before=reactProps##before,
      ~after=reactProps##after,
      ~className=?reactProps##className,
    )
  );
[@bs.obj]
external makeProps:
  (~className: 'className=?, ~after: 'after, ~before: 'before, unit) =>
  {
    .
    "before": 'before,
    "after": 'after,
    "className": option('className),
  } =
  "";
