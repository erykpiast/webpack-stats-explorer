module Styles = {
  open Css;

  let root =
    style([
      overflowX(`hidden),
      flexGrow(1.0),
      margin2(~h=Theme.Space.default, ~v=px(0)),
    ]);

  let list =
    style([
      width(`percent(100.0)),
      overflowX(`auto),
      padding2(~v=Theme.Space.double, ~h=px(0)),
      whiteSpace(`nowrap),
      maxHeight(Theme.Size.LineHeight.default),
      direction(`rtl),
      textAlign(`left),
    ]);

  let item = style([display(`inlineBlock), cursor(`pointer)]);

  let separator =
    style([
      display(`inlineBlock),
      marginLeft(Theme.Space.default),
      marginRight(Theme.Space.default),
    ]);
};

[@react.component]
let make = (~items, ~onClick) => {
  let itemsCount = items |> List.length;
  let breadcrumbs =
    items
    |> List.rev
    |> List.map2(
         (index, name) => (
            <li
              className=Styles.item
              onClick={_ => onClick(itemsCount - index + 1)}
              key={name ++ "_" ++ string_of_int(index)}>
                <ReversedText> {name |> React.string} </ReversedText>
            </li>,
            name,
         ),
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

  <div className=Styles.root>
    <ul className=Styles.list>
      {breadcrumbs |> Array.of_list |> React.array}
    </ul>
  </div>;
};