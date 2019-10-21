module Styles = {
  open Css;

  let root = style([whiteSpace(`preWrap), wordBreak(`breakAll)]);

  let removed = style([backgroundColor(Theme.Color.Removed.background)]);

  let added = style([backgroundColor(Theme.Color.Added.background)]);
};

let component = ReasonReact.statelessComponent("CodeDiff");

let make = (~after, ~before, ~className) => {
  ...component,
  render: _self =>
    <pre className={Cn.make([className, Styles.root])}>
      JsDiff.(
        make(after, before)
        |> List.map(diff =>
             switch (diff) {
             | Intact(value) => React.string(value)
             | Added(value) =>
               <span className=Styles.added> {React.string(value)} </span>
             | Removed(value) =>
               <span className=Styles.removed> {React.string(value)} </span>
             }
           )
        |> Array.of_list
        |> React.array
      )
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
        "className": 'className,
        "before": 'before,
        "after": 'after,
      },
    ) =>
    make(
      ~className=reactProps##className,
      ~before=reactProps##before,
      ~after=reactProps##after,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~after: 'after,
    ~before: 'before,
    ~className: 'className,
    unit
  ) =>
  {
    .
    "className": 'className,
    "before": 'before,
    "after": 'after,
  } =
  "";