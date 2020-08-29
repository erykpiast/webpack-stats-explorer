open Rationale.Function.Infix;

type props = {
  after: int,
  before: int,
  name: string,
  level: int,
  value: CompareEntry.entry,
  parent: option(CompareEntry.entry),
  onExpand: ReactEvent.Mouse.t => unit,
  onCollapse: ReactEvent.Mouse.t => unit,
  onSelect: (list(NavigationPath.Segment.t), ReactEvent.Mouse.t) => unit,
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
  let onPath: list(NavigationPath.Segment.t) => unit;
  let navigationPath: list(NavigationPath.Segment.t);
  let reasons: list(list(NavigationPath.Segment.t));
};

module Mapper = (Context: MapperContext) => {
  type t = {
    state: [
      | `selected
      | `reason(list(NavigationPath.Segment.t))
      | `expanded
      | `collapsed
    ],
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

  let getReasonHighlight = (level, entry) => {
    let reason =
      Context.reasons
      |> List.find_opt(reasonPath =>
           List.length(reasonPath) > level
           && entry == List.nth(reasonPath, level)
         )
      |> Utils.defaultTo([]);

    `reason(reason);
  };

  let rec expandNotModifiedEntryChildren =
          (
            kindMapper,
            ~level=0,
            ~parent=None,
            ~navigationPath=Context.navigationPath,
            ~reasons=Context.reasons,
          ) =>
    // TODO: pass reasons here as well, shorten after each step
    List.map((entry: Entry.t) => {
      let props = kindMapper(level, parent, entry);

      let (isSelected, nextNavigationPath) =
        switch (navigationPath) {
        | [segment, ...tail] =>
          switch (segment) {
          | CompareEntry.Entry(segmentEntry) => (
              segmentEntry === entry,
              tail,
            )
          | _ => (false, tail)
          }
        | [] => (false, [])
        };

      let nextReasons =
        reasons
        |> List.fold_left(
             (acc, reason) =>
               switch (reason) {
               | [segment, ...tail] =>
                 switch (segment) {
                 | CompareEntry.Entry(segmentEntry) =>
                   let matchesEntry = segmentEntry === entry;
                   if (matchesEntry) {
                     [tail, ...acc];
                   } else {
                     acc;
                   };
                 | _ => acc
                 }
               | [] => acc
               },
             [],
           );
      let isReason = List.length(nextReasons) > 0;

      if (!isReason && !isSelected) {
        {state: `collapsed, value: props, children: []};
      } else {
        let children =
          entry.children
          |> expandNotModifiedEntryChildren(
               kindMapper,
               ~level=level + 1,
               ~parent=Some(CompareEntry.Entry(entry)),
               ~navigationPath=nextNavigationPath,
               ~reasons=nextReasons,
             )
          |> sortProps;

        let state =
          if (isSelected) {
            List.length(nextNavigationPath) === 0 ? `selected : `expanded;
          } else if (isReason) {
            List.length(entry.children) === 0
              ? getReasonHighlight(level, CompareEntry.Entry(entry))
              : `expanded;
          } else {
            `collapsed;
          };

        {state, value: props, children};
      };
    });

  let createCollapseHandler = (parent, currentLevel) =>
    switch (parent) {
    | Some(parentEntry) => (
        _ => {
          parentEntry
          |> NavigationPath.Segment.make
          |> Context.onEntry(currentLevel - 1);
        }
      )
    | None => (_ => Context.onPath([]))
    };
  let createExpandHandler = (entry, currentLevel, _) =>
    entry |> NavigationPath.Segment.make |> Context.onEntry(currentLevel);

  let createSelectHandler = (navigationPath, _) =>
    Context.onPath(navigationPath);

  let mapAdded = (level, parent, entry: Entry.t) => {
    after: entry.size,
    before: 0,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onExpand: createExpandHandler(Entry(entry), level),
    onCollapse: createCollapseHandler(parent, level),
    onSelect: createSelectHandler,
  };
  let mapRemoved = (level, parent, entry: Entry.t) => {
    after: 0,
    before: entry.size,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onExpand: createExpandHandler(Entry(entry), level),
    onCollapse: createCollapseHandler(parent, level),
    onSelect: createSelectHandler,
  };
  let mapIntact = (level, parent, entry: Entry.t) => {
    after: entry.size,
    before: entry.size,
    name: entry.id,
    level,
    value: Entry(entry),
    parent,
    onExpand: createExpandHandler(Entry(entry), level),
    onCollapse: createCollapseHandler(parent, level),
    onSelect: createSelectHandler,
  };
  let mapModified = (level, parent, entry: ModifiedEntry.t(CompareEntry.t)) => {
    after: entry.size |> snd,
    before: entry.size |> fst,
    name: entry.id,
    level,
    value: ModifiedEntry(entry),
    parent,
    onExpand: createExpandHandler(ModifiedEntry(entry), level),
    onCollapse: createCollapseHandler(parent, level),
    onSelect: createSelectHandler,
  };

  let added = expandNotModifiedEntryChildren(mapAdded);
  let removed = expandNotModifiedEntryChildren(mapRemoved);
  let intact = expandNotModifiedEntryChildren(mapIntact);
  let rec modified =
          (
            ~level=0,
            ~parent=None,
            ~navigationPath=Context.navigationPath,
            ~reasons=Context.reasons,
          ) =>
    List.map((entry: ModifiedEntry.t(CompareEntry.t)) => {
      let props = mapModified(level, parent, entry);

      let (isSelected, nextNavigationPath) =
        switch (navigationPath) {
        | [segment, ...tail] =>
          switch (segment) {
          | CompareEntry.ModifiedEntry(segmentEntry) => (
              segmentEntry === entry,
              tail,
            )
          | _ => (false, tail)
          }
        | [] => (false, [])
        };
      let nextReasons =
        reasons
        |> List.fold_left(
             (acc, reason) =>
               switch (reason) {
               | [segment, ...tail] =>
                 switch (segment) {
                 | CompareEntry.ModifiedEntry(segmentEntry) =>
                   let matchesEntry = segmentEntry === entry;
                   if (matchesEntry) {
                     [tail, ...acc];
                   } else {
                     acc;
                   };
                 | _ => acc
                 }
               | [] => acc
               },
             [],
           );
      let isReason = List.length(nextReasons) > 0;

      if (!isReason && !isSelected) {
        {state: `collapsed, value: props, children: []};
      } else {
        let children =
          List.concat([
            entry.children.added
            |> added(
                 ~parent=Some(CompareEntry.ModifiedEntry(entry)),
                 ~level=level + 1,
                 ~navigationPath=nextNavigationPath,
                 ~reasons=nextReasons,
               ),
            entry.children.removed
            |> removed(
                 ~parent=Some(CompareEntry.ModifiedEntry(entry)),
                 ~level=level + 1,
                 ~navigationPath=nextNavigationPath,
                 ~reasons=nextReasons,
               ),
            entry.children.intact
            |> intact(
                 ~parent=Some(CompareEntry.ModifiedEntry(entry)),
                 ~level=level + 1,
                 ~navigationPath=nextNavigationPath,
                 ~reasons=nextReasons,
               ),
            entry.children.modified
            |> modified(
                 ~parent=Some(CompareEntry.ModifiedEntry(entry)),
                 ~level=level + 1,
                 ~navigationPath=nextNavigationPath,
                 ~reasons=nextReasons,
               ),
          ])
          |> sortProps;

        let state =
          if (isSelected) {
            List.length(nextNavigationPath) === 0 ? `selected : `expanded;
          } else {
            CompareEntry.count(entry.children) |> snd === 0
              ? getReasonHighlight(level, CompareEntry.ModifiedEntry(entry))
              : `expanded;
          };

        {state, value: props, children};
      };
    });

  let rec flatten = (hasParent, nested) =>
    Utils.List.flatMap(
      ({state, value, children}) =>
        [
          (state, value, (hasChildren(value.value), hasParent)),
          ...flatten(true, children),
        ],
      nested,
    );
};

let resolveReason = (initialEntry, chunkId) =>
  CompareEntry.(
    Rationale.Option.Infix.(
      List.tl
      ||> List.cons(chunkId)
      ||> List.fold_left(
            ((acc, children: children), reasonPathSegment) => {
              let reasonPathEntry =
                switch (children) {
                | NotModifiedChildren(children) =>
                  children
                  |> List.find_opt(Entry.hasId(reasonPathSegment))
                  <$> (entry => Entry(entry))
                | ModifiedChildren(children) =>
                  List.concat([
                    children.added,
                    children.removed,
                    children.intact,
                  ])
                  |> List.find_opt(Entry.hasId(reasonPathSegment))
                  <$> (entry => Entry(entry))
                  |? (
                    children.modified
                    |> List.find_opt(ModifiedEntry.hasId(reasonPathSegment))
                    <$> (entry => ModifiedEntry(entry))
                  )
                };

              switch (reasonPathEntry) {
              | None => (acc, children)
              | Some(entry) => (
                  [entry, ...acc],
                  switch (entry) {
                  | Entry({children}) => NotModifiedChildren(children)
                  | ModifiedEntry({children}) => ModifiedChildren(children)
                  },
                )
              };
            },
            ([], initialEntry),
          )
    )
  );

let mapToProps = (onEntry, onPath, navigationPath, comp: CompareEntry.t) => {
  /* TODO: Map it to list of entries */
  let reasons =
    (
      switch (navigationPath) {
      | [] => []
      | navigationPath =>
        CompareEntry.(
          {
            let last = navigationPath |> List.rev |> List.hd;
            let firstId =
              switch (navigationPath |> List.hd) {
              | Entry(entry) => entry.id
              | ModifiedEntry(entry) => entry.id
              };
            let resolve = resolveReason(ModifiedChildren(comp), firstId);

            switch (last) {
            | Entry(entry) => entry.reasons |> List.map(resolve ||> fst)
            | ModifiedEntry(entry) =>
              List.concat([
                entry.reasons |> fst |> List.map(resolve ||> fst),
                entry.reasons |> snd |> List.map(resolve ||> fst),
              ])
            };
          }
        )
      }
    )
    |> List.map(List.rev);

  module TheMapper =
    Mapper({
      let onEntry = onEntry;
      let onPath = onPath;
      let navigationPath = navigationPath;
      let reasons = reasons;
    });

  List.concat([
    TheMapper.added(comp.added),
    TheMapper.removed(comp.removed),
    TheMapper.intact(comp.intact),
    TheMapper.modified(comp.modified),
  ])
  |> TheMapper.sortProps
  |> TheMapper.flatten(false);
};
