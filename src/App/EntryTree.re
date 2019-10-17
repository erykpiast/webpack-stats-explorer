open Rationale.Function.Infix;

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

  module Level = {
    let l0 = style([paddingLeft(Theme.Space.default)]);

    let l1 = style([paddingLeft(Theme.Space.triple)]);

    let l2 = style([paddingLeft(Theme.Space.fivefold)]);

    let l3 = style([paddingLeft(Theme.Space.sevenfold)]);
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
  let onEntry: (int, State.NavigationPath.Segment.t) => unit;
  let navigationPath: list(State.NavigationPath.Segment.t);
};

module Mapper = (Context: MapperContext) => {
  type t = {
    selected: bool,
    value: props,
    children: list(t),
  };

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
          | Entry(segmentEntry) =>
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
    onChange:
      State.NavigationPath.Segment.make(Added) ||> Context.onEntry(level),
  };
  let mapRemoved = (level, parent, entry: Entry.t) => {
    after: 0,
    before: entry.size,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onChange:
      State.NavigationPath.Segment.make(Removed) ||> Context.onEntry(level),
  };
  let mapIntact = (level, parent, entry: Entry.t) => {
    after: entry.size,
    before: entry.size,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onChange:
      State.NavigationPath.Segment.make(Intact) ||> Context.onEntry(level),
  };
  let mapModified = (level, parent, entry: ModifiedEntry.t(CompareEntry.t)) => {
    after: entry.size |> snd,
    before: entry.size |> fst,
    name: entry.id,
    level,
    value: ModifiedEntry(entry),
    parent,
    onChange:
      State.NavigationPath.Segment.make(Modified) ||> Context.onEntry(level),
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

  let rec flatten = nested =>
    Utils.List.flatMap(
      ({selected, value, children}) =>
        [(selected, value), ...flatten(children)],
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
  |> TheMapper.flatten;
};

let getLevelClass = level =>
  switch (level) {
  | 0 => Styles.Level.l0
  | 1 => Styles.Level.l1
  | 2 => Styles.Level.l2
  | _ => Styles.Level.l3
  };

let component = ReasonReact.statelessComponent("EntryTree");

let make =
    (
      ~onEntry,
      ~comp: CompareEntry.t,
      ~navigationPath: State.NavigationPath.t,
      _children,
    ) => {
  ...component,
  render: _self => {
    let props = mapToProps(onEntry, navigationPath, comp);

    switch (props) {
    | [] => ReasonReact.null
    | data =>
      <ul className=Styles.list>
        ...{
             data
             |> List.map(
                  (
                    (selected, {after, before, value, name, level, onChange}),
                  ) =>
                  <li
                    onClick={_ => onChange(value)}
                    className={Cn.make([
                      Styles.item,
                      Cn.ifTrue(Styles.selectedItem, selected),
                      getLevelClass(level),
                    ])}
                    title=name>
                    <ReversedText className=Styles.name>
                      ...{name |> ReasonReact.string}
                    </ReversedText>
                    {before !== 0 && after !== 0
                       ? <Size className=Styles.size value=after />
                       : ReasonReact.null}
                    <NumericDiff className=Styles.diff after before />
                  </li>
                )
             |> Array.of_list
           }
      </ul>
    };
  },
};