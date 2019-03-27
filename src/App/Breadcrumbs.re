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

let renderName = (item) => State.NavigationPath.Segment.Item.(switch (item) {
  | Chunk(chunk) => Compare.Chunks.(switch (chunk) {
    | Summary(summary) => summary.name
    | ModifiedSummary(summary) => summary.name
  })
  | Module(module_) => Compare.Modules.(switch (module_) {
    | Summary(summary) => summary.name
    | ModifiedSummary(summary) => summary.name
  })
});

let renderItem = Compare.Kind.((item, kind) => {
  let (badgeClassName, badgeText) = switch (kind) {
  | Added => (Styles.Badge.added, "A")
  | Removed => (Styles.Badge.removed, "R")
  | Intact => (Styles.Badge.intact, "I")
  | Modified => (Styles.Badge.modified, "M")
  };

  <>
    <span className=badgeClassName>{badgeText |> ReasonReact.string}</span>
    {renderName(item) |> ReasonReact.string}
  </>
});

let component = ReasonReact.statelessComponent("Breadcrumbs");

let make = (~items, _children) => {
  ...component,
  render: (_self) => {
    <ul className=Styles.wrapper>
      ...(items |> List.map(item => {
        <li className=Styles.item>{renderItem(fst(item), snd(item))}</li>
      }) |> Array.of_list)
    </ul>
  }
}