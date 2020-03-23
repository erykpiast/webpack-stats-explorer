open Rationale.Function.Infix;

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
      flexShrink(0.0),
    ]);

  let item =
    style([
      display(`flex),
      cursor(`pointer),
      justifyContent(`spaceBetween),
      padding(Theme.Space.default),
    ]);

  let selectedItem =
    style([backgroundColor(Theme.Color.Background.selected)]);

  let parentItem =
    style([
      before([
        contentRule(`text(rightTriangle)),
        marginRight(Theme.Space.default),
        fontSize(em(1.136)),
        color(Theme.Color.Border.default),
      ]),
    ]);

  let expandedParentItem =
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

type props = {
  after: int,
  before: int,
  name: string,
  level: int,
  value: CompareEntry.entry,
  parent: option(CompareEntry.entry),
  onChange: CompareEntry.entry => unit,
};

let encode = r =>
  Json.Encode.(
    object_([
      ("after", r.after |> int),
      ("before", r.before |> int),
      ("level", r.level |> int),
      ("name", r.name |> string),
    ])
  );

module type MapperContext = {
  let onEntry: (int, NavigationPath.Segment.t) => unit;
  let navigationPath: list(NavigationPath.Segment.t);
};

module Mapper = (Context: MapperContext) => {
  type t = {
    selected: bool,
    value: props,
    children: list(t),
  };

  let hasChildren =
    CompareEntry.(
      fun
      | Entry(entry) => List.length(entry.children) > 0
      | ModifiedEntry(entry) => entry.children |> count |> snd > 0
    );

  let sortProps =
    List.sort(({value: a}, {value: b}) => {
      let aDiff = a.after - a.before;
      let bDiff = b.after - b.before;
      let diffOfDiffs = bDiff - aDiff;

      if (diffOfDiffs === 0) {
        0;
      } else if (aDiff === 0) {
        1;
      } else if (bDiff === 0) {
        (-1);
      } else {
        diffOfDiffs;
      };
    });

  let rec expandNotModifiedEntryChildren =
          (
            expectedKind,
            kindMapper,
            ~level=0,
            ~parent=None,
            ~navigationPath=Context.navigationPath,
          ) =>
    List.map((entry: Entry.t) => {
      let props = kindMapper(level, parent, entry);

      switch (navigationPath) {
      | [] => {selected: false, value: props, children: []}
      | [(segment, kind), ...tail] =>
        if (kind === expectedKind) {
          switch (segment) {
          | CompareEntry.Entry(segmentEntry) =>
            if (segmentEntry == entry) {
              let children =
                entry.children
                |> expandNotModifiedEntryChildren(
                     expectedKind,
                     kindMapper,
                     ~level=level + 1,
                     ~parent=Some(CompareEntry.Entry(entry)),
                     ~navigationPath=tail,
                   )
                |> sortProps;
              {selected: true, value: props, children};
            } else {
              {selected: false, value: props, children: []};
            }
          | _ => {selected: false, value: props, children: []}
          };
        } else {
          {selected: false, value: props, children: []};
        }
      };
    });

  let mapAdded = (level, parent, entry: Entry.t) => {
    after: entry.size,
    before: 0,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onChange: NavigationPath.Segment.make(Added) ||> Context.onEntry(level),
  };
  let mapRemoved = (level, parent, entry: Entry.t) => {
    after: 0,
    before: entry.size,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onChange:
      NavigationPath.Segment.make(Removed) ||> Context.onEntry(level),
  };
  let mapIntact = (level, parent, entry: Entry.t) => {
    after: entry.size,
    before: entry.size,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onChange: NavigationPath.Segment.make(Intact) ||> Context.onEntry(level),
  };
  let mapModified = (level, parent, entry: ModifiedEntry.t(CompareEntry.t)) => {
    after: entry.size |> snd,
    before: entry.size |> fst,
    name: entry.id,
    level,
    value: ModifiedEntry(entry),
    parent,
    onChange:
      NavigationPath.Segment.make(Modified) ||> Context.onEntry(level),
  };

  let added = expandNotModifiedEntryChildren(Added, mapAdded);
  let removed = expandNotModifiedEntryChildren(Removed, mapRemoved);
  let intact = expandNotModifiedEntryChildren(Intact, mapIntact);
  let rec modified =
          (~level=0, ~parent=None, ~navigationPath=Context.navigationPath) =>
    List.map((entry: ModifiedEntry.t(CompareEntry.t)) => {
      let props = mapModified(level, parent, entry);

      switch (navigationPath) {
      | [] => {selected: false, value: props, children: []}
      | [(segment, kind), ...tail] =>
        if (kind === Modified) {
          switch (segment) {
          | ModifiedEntry(segmentEntry) =>
            if (segmentEntry == entry) {
              let parent = Some(CompareEntry.ModifiedEntry(entry));
              let level = level + 1;
              let navigationPath = tail;
              let children =
                List.concat([
                  entry.children.added
                  |> added(~parent, ~level, ~navigationPath),
                  entry.children.removed
                  |> removed(~parent, ~level, ~navigationPath),
                  entry.children.intact
                  |> intact(~parent, ~level, ~navigationPath),
                  entry.children.modified
                  |> modified(~parent, ~level, ~navigationPath),
                ])
                |> sortProps;
              {selected: true, value: props, children};
            } else {
              {selected: false, value: props, children: []};
            }
          | _ => {selected: false, value: props, children: []}
          };
        } else {
          {selected: false, value: props, children: []};
        }
      };
    });

  let rec flatten = (hasParent, nested) =>
    Utils.List.flatMap(
      ({selected, value, children}) =>
        [
          (
            selected,
            List.length(children) > 0,
            value,
            (hasChildren(value.value), hasParent),
          ),
          ...flatten(true, children),
        ],
      nested,
    );
};

let mapToProps = (onEntry, navigationPath, comp: CompareEntry.t) => {
  module TheMapper =
    Mapper({
      let onEntry = onEntry;
      let navigationPath = navigationPath;
    });
  List.concat([
    comp.added |> TheMapper.added,
    comp.removed |> TheMapper.removed,
    comp.intact |> TheMapper.intact,
    comp.modified |> TheMapper.modified,
  ])
  |> TheMapper.sortProps
  |> TheMapper.flatten(false);
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
  | (true, true) => Cn.make([Styles.parentItem, Styles.childItem])
  | (true, false) => Styles.parentItem
  | (false, true) => Styles.childItem
  | (false, false) => "";

[@react.component]
let make =
    (~onEntry, ~comp: CompareEntry.t, ~navigationPath: NavigationPath.t) => {
  let props = mapToProps(onEntry, navigationPath, comp);

  switch (props) {
  | [] => React.null
  | data =>
    <ul className=Styles.list>
      {data
       |> List.map(
            (
              (
                selected,
                expanded,
                {after, before, value, name, level, onChange},
                familyRelations,
              ),
            ) => {
            let isModifiedOrIntact = before !== 0 && after !== 0;

            <li
              onClick={_ => onChange(value)}
              className={Cn.make([
                Styles.item,
                Cn.ifTrue(Styles.selectedItem, selected),
                Cn.ifTrue(Styles.expandedParentItem, expanded),
                getLevelClass(level),
                getFamilyClass(familyRelations),
              ])}
              title=name
              key={string_of_int(level) ++ name}>
              <ReversedText className=Styles.name>
                ...{name |> React.string}
              </ReversedText>
              {isModifiedOrIntact
                 ? <Size className=Styles.size value=after /> : React.null}
              <NumericDiff
                className={Cn.make([
                  Styles.diff,
                  Cn.ifTrue(Styles.soleDiff, !isModifiedOrIntact),
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