module Styles = {
  open Css;

  let wrapper = style([
    display(`flex),
    width(`percent(100.0)),
  ]);

  let item = style([
    display(block),
  ]);

  module Badge = {
    let badgeRules = [
      display(`inlineBlock),
      padding(px(2)),
      border(px(1), solid, rgb(0, 0, 0)),
      borderRadius(px(2)),
      width(em(1.2)),
      textAlign(`center),
      marginRight(px(4)),
    ];

    let added = style([
      backgroundColor(Theme.worseColor),
      ...badgeRules,
    ]);

    let intact = style(badgeRules);

    let modified = style([
      backgroundColor(Theme.changeColor),
      ...badgeRules,
    ]);

    let removed = style([
      backgroundColor(Theme.betterColor),
      ...badgeRules,
    ]);
  };
};

open State;

let renderName = (item) => switch (item) {
  | Chunk(chunk) => switch (chunk) {
    | Compare.Chunks.Summary(summary) => summary.name
    | Compare.Chunks.ModifiedSummary(summary) => summary.name
  }
  | Module(module_) => switch (module_) {
    | Compare.Modules.Summary(summary) => summary.name
    | Compare.Modules.ModifiedSummary(summary) => summary.name
  }
};

let renderItem = (item) => switch (item) {
  | NavigationPath.Added(item) => (item, Styles.Badge.added, "A")
  | NavigationPath.Removed(item) => (item, Styles.Badge.removed, "R")
  | NavigationPath.Intact(item) => (item, Styles.Badge.intact, "I")
  | NavigationPath.Modified(item) => (item, Styles.Badge.modified, "M")
  } |> ((segment, badgeClassName, badgeText)) => <>
    <span className=badgeClassName>{badgeText |> ReasonReact.string}</span>
    {renderName(segment) |> ReasonReact.string}
  </>;

let component = ReasonReact.statelessComponent("Breadcrumbs");

let make = (~items, _children) => {
  ...component,
  render: (_self) => {
    <ul className=Styles.wrapper>
      ...(items |> List.map(item => {
        <li className=Styles.item>{renderItem(item)}</li>
      }) |> Array.of_list)
    </ul>
  }
}