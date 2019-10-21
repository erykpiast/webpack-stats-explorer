let component = ReasonReact.statelessComponent("EntryOverview");

module Styles = {
  open Css;

  let root =
    style([
      alignItems(`center),
      display(`flex),
      flexDirection(`column),
      fontSize(em(2.0)),
      height(`percent(100.0)),
      justifyContent(`center),
      position(`relative),
    ]);
  let arrow =
    style([
      position(`absolute),
      left(Theme.Space.double),
      top(Theme.Space.double),
    ]);
  let size = style([display(`block), color(Theme.Color.Text.secondary)]);
  let count = style([color(Theme.Color.Text.primary), margin(px(0))]);
  let diff = style([display(`block)]);
};

let make = (~size, ~count, _children) => {
  ...component,
  render: _self =>
    <section className=Styles.root>
      <PointingArrow className=Styles.arrow>
        ("Choose the" |> React.string)
        <br />
        ("chunk here!" |> React.string)
      </PointingArrow>
      <p className=Styles.count>
        (count |> Utils.pluralize(L10N.chunk, L10N.chunks) |> React.string)
      </p>
      <Size className=Styles.size value=(snd(size)) />
      <NumericDiff
        className=Styles.diff
        after=(snd(size))
        before=(fst(size))
      />
    </section>,
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
        "count": 'count,
        "size": 'size,
        "children": 'children,
      },
    ) =>
    make(
      ~count=reactProps##count,
      ~size=reactProps##size,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (~children: 'children, ~size: 'size, ~count: 'count, unit) =>
  {
    .
    "count": 'count,
    "size": 'size,
    "children": 'children,
  } =
  "";
