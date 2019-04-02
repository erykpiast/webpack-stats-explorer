module Styles = {
  open Css;

  let wrapper = style([
    display(`flex),
    alignItems(`center),
    width(`percent(100.0)),
  ]);

  let item = style([
    display(block),
  ]);

  let segmentRules = [
    display(`inlineBlock),
    padding(px(2)),
    width(em(1.2)),
    textAlign(`center),
    marginRight(px(4)),
  ];

  let separator = style(segmentRules);

  module Badge = {
    let badgeRules = [
      border(px(1), solid, rgb(0, 0, 0)),
      borderRadius(px(2)),
      ...segmentRules
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
    {item |> renderName |> ReasonReact.string}
  </>
});

let component = ReasonReact.statelessComponent("Breadcrumbs");

let make = (~items, ~onClick, _children) => {
  ...component,
  render: (_self) => {
    let head = <li className=Styles.item onClick=((_) => onClick(0))>
      {L10N.breadcrumbsRoot |> ReasonReact.string}
    </li>;
    let tail = items |> List.map2((index, (item, kind)) => {
      <li className=Styles.item onClick=((_) => onClick(index))>
        {renderItem(item, kind)}
      </li>
    }, Rebase.List.range(1, List.length(items)));
    let separator = <li className=Styles.separator>{">" |> ReasonReact.string}</li>;
    let breadcrumbs = [head, ...tail] |> Utils.List.join(separator);

    <ul className=Styles.wrapper>
      ...(breadcrumbs |> Array.of_list)
    </ul>
  }
}