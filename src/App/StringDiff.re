module Styles = {
  open Css;

  let before =
    style([
      display(inlineBlock),
      backgroundColor(Theme.Color.Added.default),
      padding(Theme.padding),
    ]);

  let after =
    style([
      display(inlineBlock),
      backgroundColor(Theme.Color.Removed.default),
      padding(Theme.padding),
    ]);
};

let component = ReasonReact.statelessComponent("StringDiff");

let make = (_children, ~after, ~before) => {
  ...component,
  render: _self =>
    <>
      <span className=Styles.before> (React.string(before)) </span>
      <span className=Styles.after> (React.string(after)) </span>
    </>,
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
        "children": 'children,
      },
    ) =>
    make(
      ~before=reactProps##before,
      ~after=reactProps##after,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (~children: 'children, ~after: 'after, ~before: 'before, unit) =>
  {
    .
    "before": 'before,
    "after": 'after,
    "children": 'children,
  } =
  "";
