module Styles = {
  open Css;

  let root = style([whiteSpace(`preWrap), wordBreak(`breakAll)]);

  let removed = style([backgroundColor(Theme.Color.Removed.background)]);

  let added = style([backgroundColor(Theme.Color.Added.background)]);
};

[@react.component]
let make = (~after, ~before, ~className) => {
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
  </pre>;
};