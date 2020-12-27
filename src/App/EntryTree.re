open EntryTreeMapper;

let downTriangle = {js|▼|js};
let rightTriangle = {js|▶|js};

module Styles = {
  open Css;

  let list =
    style([
      listStyleType(`none),
      padding(px(0)),
      margin(px(0)),
      maxHeight(`percent(100.0)),
      overflowY(`auto),
      overflowX(`hidden),
      flexShrink(0.0),
    ]);

  let item =
    style([
      display(`flex),
      cursor(`pointer),
      justifyContent(`spaceBetween),
      padding(Theme.Space.default),
      before([display(`none)]),
    ]);

  let selectedItem =
    style([
      backgroundColor(Theme.Color.Background.selected),
      before([contentRule(`text(downTriangle)), fontSize(em(1.02))]),
    ]);

  let reasonItem = style([backgroundColor(Theme.Color.Background.reason)]);

  let parentItem =
    style([
      before([
        display(`block),
        marginRight(Theme.Space.default),
        color(Theme.Color.Border.default),
      ]),
    ]);

  let collapsedItem =
    style([
      before([contentRule(`text(rightTriangle)), fontSize(em(1.136))]),
    ]);

  let expandedItem =
    style([
      before([contentRule(`text(downTriangle)), fontSize(em(1.02))]),
    ]);

  let levelGradient =
    repeatingLinearGradient(
      deg(90.0),
      [
        (px(0), `transparent),
        (Theme.Space.double, `transparent),
        (Theme.Space.double, Theme.Color.Border.default),
        (px(Theme.Space.Raw.double + 1), Theme.Color.Border.default),
        (px(Theme.Space.Raw.double + 1), `transparent),
        (Theme.Space.triple, `transparent),
      ],
    );

  let childItem =
    style([
      backgroundImage(levelGradient),
      backgroundRepeat(`noRepeat),
      backgroundSize(`size((px(0), px(0)))),
    ]);

  let name =
    style([
      overflow(`hidden),
      flexShrink(1.0),
      marginRight(Theme.Space.default),
      textOverflow(`ellipsis),
      whiteSpace(`nowrap),
    ]);

  let size =
    style([
      marginLeft(`auto),
      marginRight(Theme.Space.default),
      color(Theme.Color.Text.secondary),
      flexShrink(0.0),
    ]);

  let diff = style([flexShrink(0.0)]);
  let soleDiff = style([marginLeft(`auto)]);

  module Level = {
    let l0 = style([paddingLeft(Theme.Space.default)]);

    let l1 =
      style([
        paddingLeft(Theme.Space.quadruple),
        backgroundSize(`size((Theme.Space.quadruple, `percent(100.0)))),
      ]);

    let l2 =
      style([
        paddingLeft(Theme.Space.sevenfold),
        backgroundSize(`size((Theme.Space.sevenfold, `percent(100.0)))),
      ]);

    let l3 =
      style([
        paddingLeft(Theme.Space.tenfold),
        backgroundSize(`size((Theme.Space.tenfold, `percent(100.0)))),
      ]);

    let l4 =
      style([
        paddingLeft(Theme.Space.thirteenfold),
        backgroundSize(`size((Theme.Space.thirteenfold, `percent(100.0)))),
      ]);

    let l5 =
      style([
        paddingLeft(Theme.Space.hexteenfold),
        backgroundSize(`size((Theme.Space.hexteenfold, `percent(100.0)))),
      ]);

    let l6 =
      style([
        paddingLeft(Theme.Space.nineteenfold),
        backgroundSize(`size((Theme.Space.nineteenfold, `percent(100.0)))),
      ]);
  };
};

let getLevelClass = level =>
  switch (level) {
  | 0 => Styles.Level.l0
  | 1 => Styles.Level.l1
  | 2 => Styles.Level.l2
  | 3 => Styles.Level.l3
  | 4 => Styles.Level.l4
  | 5 => Styles.Level.l5
  | _ => Styles.Level.l6
  };

let getFamilyClass =
  fun
  | (true, true) => Cn.fromList([Styles.parentItem, Styles.childItem])
  | (true, false) => Styles.parentItem
  | (false, true) => Styles.childItem
  | (false, false) => "";

[@react.component]
let make =
    (
      ~onEntry,
      ~onPath,
      ~comp: CompareEntry.t,
      ~navigationPath: NavigationPath.t,
    ) => {
  let props = mapToProps(onEntry, onPath, navigationPath, comp);

  switch (props) {
  | [] => React.null
  | data =>
    <ul className=Styles.list id="entry-tree">
      {data
       |> List.mapi(
            (
              index,
              (
                state,
                {after, before, name, level, onExpand, onCollapse, onSelect},
                familyRelations,
              ),
            ) => {
            let isModifiedOrIntact = before !== 0 && after !== 0;
            let (isParent, _) = familyRelations;
            let onClick =
              switch (state, isParent) {
              | (`reason(path), _) => onSelect(path)
              | (`expanded, _) => onCollapse
              | (`selected, true) => onCollapse
              | (`selected, false) => Utils.noop
              | (`collapsed, _) => onExpand
              };
            let stateClassName =
              switch (state) {
              | `selected => Styles.selectedItem
              | `reason(_) => Styles.reasonItem
              | `expanded => Styles.expandedItem
              | `collapsed => Styles.collapsedItem
              };

            <li
              onClick
              className={Cn.fromList([
                Styles.item,
                stateClassName,
                getLevelClass(level),
                getFamilyClass(familyRelations),
              ])}
              title=name
              id={"entry-tree-item-" ++ string_of_int(index)}
              key={
                string_of_int(level)
                ++ "_"
                ++ name
                ++ "_"
                ++ string_of_int(after)
                ++ "_"
                ++ string_of_int(before)
              }>
              <ReversedText className=Styles.name>
                ...{name |> React.string}
              </ReversedText>
              {isModifiedOrIntact
                 ? <Size className=Styles.size value=after /> : React.null}
              <NumericDiff
                className={Cn.fromList([
                  Styles.diff,
                  Cn.on(Styles.soleDiff, !isModifiedOrIntact),
                ])}
                after
                before
              />
            </li>;
          })
       |> Array.of_list
       |> React.array}
    </ul>
  };
};
