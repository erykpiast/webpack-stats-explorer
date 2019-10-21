module Styles = {
  open Css;

  let list =
    style([
      display(`flex),
      alignItems(`center),
      width(`percent(100.0)),
      margin(px(0)),
      marginLeft(Theme.Space.double),
      padding(px(0)),
    ]);

  let item = style([display(block), cursor(`pointer)]);

  let separator =
    style([
      display(`inlineBlock),
      marginLeft(Theme.Space.default),
      marginRight(Theme.Space.default),
    ]);
};

let renderName = item =>
  switch (item) {
  | CompareEntry.Entry({id}) => id
  | CompareEntry.ModifiedEntry({id}) => id
  };

let component = ReasonReact.statelessComponent("Breadcrumbs");

let make = (~items, ~onClick) => {
  ...component,
  render: _self => {
    let separator =
      <li className=Styles.separator> {{js|▷|js} |> React.string} </li>;

    let breadcrumbs =
      items
      |> List.map2(
           (index, (item, _: CompareKind.t)) =>
             <li className=Styles.item onClick={_ => onClick(index)}>
               {item |> renderName |> React.string}
             </li>,
           Rebase.List.range(1, List.length(items)),
         )
      |> Utils.List.join(separator);

    <ul className=Styles.list>
      {breadcrumbs |> Array.of_list |> React.array}
    </ul>;
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
        "onClick": 'onClick,
        "items": 'items,
      },
    ) =>
    make(~onClick=reactProps##onClick, ~items=reactProps##items)
  );
[@bs.obj]
external makeProps:
  (~items: 'items, ~onClick: 'onClick, unit) =>
  {
    .
    "onClick": 'onClick,
    "items": 'items,
  } =
  "";