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
  State.NavigationPath.Segment.Item.(
    switch (item) {
    | Chunk(chunk) =>
      Compare.Chunks.(
        switch (chunk) {
        | Summary(summary) => summary.name
        | ModifiedSummary(summary) => summary.name
        }
      )
    | Module(module_) =>
      Compare.Modules.(
        switch (module_) {
        | Summary(summary) => summary.name
        | ModifiedSummary(summary) => summary.name
        }
      )
    | Entry(entry) => switch (entry) {
      | CompareEntry.Entry({id}) => id
      | CompareEntry.ModifiedEntry({id}) => id
      }
    }
  );

let component = ReasonReact.statelessComponent("Breadcrumbs");

let make = (~items, ~onClick, _children) => {
  ...component,
  render: _self => {
    let separator =
      <li className=Styles.separator>
        {{js|▷|js} |> ReasonReact.string}
      </li>;

    let breadcrumbs =
      items
      |> List.map2(
           (index, (item, _)) =>
             <li className=Styles.item onClick={_ => onClick(index)}>
               {item |> renderName |> ReasonReact.string}
             </li>,
           Rebase.List.range(1, List.length(items)),
         )
      |> Utils.List.join(separator);

    <ul className=Styles.list> ...{breadcrumbs |> Array.of_list} </ul>;
  },
};