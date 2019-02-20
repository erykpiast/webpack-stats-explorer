module Styles = {
  open Css;

  let removed = style([
    backgroundColor(Theme.worseColor),
  ]);

  let added = style([
    backgroundColor(Theme.betterColor),
  ]);
};

let component = ReasonReact.statelessComponent("CodeDiff");

let make = (
  _children,
  ~after,
  ~before,
) => {
  ...component,
  render: _self => <pre>
    ...JsDiff.(make(before, after) |> List.map((diff) => switch diff {
    | Intact(value) => ReasonReact.string(value)
    | Added(value) => <span className=Styles.added>{ReasonReact.string(value)}</span>
    | Removed(value) => <span className=Styles.removed>{ReasonReact.string(value)}</span>
    }) |> Array.of_list)
  </pre>
};
