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

[@react.component]
let make = (~items, ~onClick) => {
  let breadcrumbs =
    items
    |> List.map2(
         (index, (item, _: CompareKind.t)) => {
           let name = item |> renderName;
           (
             <li className=Styles.item onClick={_ => onClick(index)} key=name>
               {name |> React.string}
             </li>,
             name,
           );
         },
         Rebase.List.range(1, List.length(items)),
       )
    |> List.fold_left(
         (acc, (item, name)) => {
           [
             item,
             <li className=Styles.separator key={name ++ "_separator"}>
               {{js|▷|js} |> React.string}
             </li>,
           ]
           |> List.append(acc)
         },
         [],
       )
      |> Utils.List.removeLast;

  <ul className=Styles.list>
    {breadcrumbs |> Array.of_list |> React.array}
  </ul>;
};