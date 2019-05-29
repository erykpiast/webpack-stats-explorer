module Styles = {
  open Css;

  let removed = style([backgroundColor(Theme.Color.Removed.background)]);

  let added = style([backgroundColor(Theme.Color.Added.background)]);
};

let component = ReasonReact.statelessComponent("CodeDiff");

let make = (~after, ~before, ~className, _children) => {
  ...component,
  render: _self =>
    <pre className>
      ...JsDiff.(
           make(before, after)
           |> List.map(diff =>
                switch (diff) {
                | Intact(value) => ReasonReact.string(value)
                | Added(value) =>
                  <span className=Styles.added>
                    {ReasonReact.string(value)}
                  </span>
                | Removed(value) =>
                  <span className=Styles.removed>
                    {ReasonReact.string(value)}
                  </span>
                }
              )
           |> Array.of_list
         )
    </pre>,
};