open CompareEntry;
open CompareKind;

module Styles = {
  open Css;

  let term = style([fontWeight(`bold), display(`none)]);

  let definition = style([margin(px(0))]);

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
      width(`percent(100.0)),
    ]);

  let list = style([margin(px(0))]);

  let header =
    style([
      flexGrow(0.0),
      borderBottom(px(1), `solid, Theme.Color.Border.default),
    ]);

  let modules =
    style([
      backgroundColor(Theme.Color.Background.default),
      width(Theme.Space.triplehexfold),
      marginLeft(`auto),
      height(`percent(100.0)),
    ]);

  let status =
    style([
      textTransform(`uppercase),
      marginLeft(Theme.Space.double),
      marginTop(Theme.Space.double),
    ]);

  let name =
    style([
      fontSize(rem(2.0)),
      wordBreak(`breakAll),
      marginLeft(Theme.Space.double),
    ]);

  let size = style([fontSize(rem(1.2)), marginTop(Theme.Space.default)]);

  let sizeTerm = style([display(`block), marginRight(Theme.Space.default)]);

  let content =
    style([
      display(`flex),
      flexGrow(1.0),
      overflow(`auto),
      maxHeight(`percent(100.0)),
    ]);

  let code =
    style([
      padding(Theme.Space.default),
      whiteSpace(`preWrap),
      wordBreak(`breakAll),
    ]);

  module Kind = {
    let added = style([color(Theme.Color.Added.default)]);
    let removed = style([color(Theme.Color.Removed.default)]);
    let intact = style([color(Theme.Color.Intact.default)]);
    let modified = style([color(Theme.Color.Modified.default)]);
  };
};

let nbsp = {js|  |js};

let getKindMessage = kind =>
  switch (kind) {
  | Added => L10N.Kind.added
  | Removed => L10N.Kind.removed
  | Intact => L10N.Kind.intact
  | Modified => L10N.Kind.modified
  };

let getKindClassName = kind =>
  switch (kind) {
  | Added => Styles.Kind.added
  | Removed => Styles.Kind.removed
  | Intact => Styles.Kind.intact
  | Modified => Styles.Kind.modified
  };

module Mapper = {
  type a = entry;

  let componentName = "EntrySummary";
  let getName = entry =>
    switch (entry) {
    | Entry(entry) => entry.id
    | ModifiedEntry(entry) => entry.id
    };

  let getSize = entry =>
    switch (entry) {
    | Entry(entry) => entry.size
    | ModifiedEntry(entry) => entry.size |> snd
    };

  let getStatSize = entry =>
    switch (entry) {
    | Entry(entry) =>
      switch (entry.stat) {
      | Some({size}) => size
      | None => 0
      }
    | ModifiedEntry(entry) =>
      switch (entry.stat) {
      | Some({size}) => size |> snd
      | None => 0
      }
    };

  let getOriginalSize = entry =>
    switch (entry) {
    | Entry(entry) =>
      switch (entry.original) {
      | Some({size}) => Some(size)
      | None => None
      }
    | ModifiedEntry(entry) =>
      switch (entry.original) {
      | Some({size}) => Some(size |> snd)
      | None => None
      }
    };
  let getParsedSize = entry =>
    switch (entry) {
    | Entry(entry) =>
      switch (entry.parsed) {
      | Some({size}) => Some(size)
      | None => None
      }
    | ModifiedEntry(entry) =>
      switch (entry.parsed) {
      | Some({size}) => Some(size |> snd)
      | None => None
      }
    };
  let getStatSource = entry =>
    switch (entry) {
    | Entry(entry) =>
      (
        switch (entry.stat) {
        | Some({source}) => source
        | None => ""
        }
      )
      |> (
        code => <pre className=Styles.code> {code |> ReasonReact.string} </pre>
      )
    | ModifiedEntry(entry) =>
      switch (entry.stat) {
      | Some({source}) =>
        <CodeDiff
          className=Styles.code
          before={source |> fst}
          after={source |> snd}
        />
      | None => ReasonReact.null
      }
    };
  let getOriginalSource = _ => None;
  let getParsedSource = _ => None;
  let getSource = getStatSource;

  let getModules = entry =>
    switch (entry) {
    | Entry(entry) => Some(NotModifiedChildren(entry.children))
    | ModifiedEntry(entry) => Some(ModifiedChildren(entry.children))
    };
};

let component = ReasonReact.statelessComponent(Mapper.componentName);

let make = (~data, ~kind, ~onEntry, ~selected, _children) => {
  ...component,
  render: _self => {
    let statSize = data |> Mapper.getStatSize;
    let originalSize = data |> Mapper.getOriginalSize;
    let parsedSize = data |> Mapper.getParsedSize;

    let modules =
      switch (data |> Mapper.getModules) {
      | Some(modules) =>
        Rationale.Option.Infix.(
          switch (modules) {
          | NotModifiedChildren(entries) =>
            <EntryList
              className=Styles.modules
              entries
              kind
              onEntry
              selected={selected <$> Mapper.getName}
            />
          | ModifiedChildren(entries) =>
            <EntryCompare
              className=Styles.modules
              entries
              onEntry
              selected={selected <$> Mapper.getName}
            />
          }
        )
      | None => ReasonReact.null
      };

    let renderSize = (label, size) =>
      <>
        <dt className={Cn.make([Styles.term, Styles.sizeTerm])}>
          {label |> ReasonReact.string}
        </dt>
        <dd className=Styles.definition> <Size value=size /> </dd>
      </>;

    <div className=Styles.wrapper>
      <header className=Styles.header>
        <dl className=Styles.list>
          <div className=Styles.status>
            <dt className=Styles.term>
              {L10N.Summary.status |> ReasonReact.string}
            </dt>
            <dd
              className={Cn.make([
                Styles.definition,
                getKindClassName(kind),
              ])}>
              {kind |> getKindMessage |> ReasonReact.string}
              {nbsp |> ReasonReact.string}
              {L10N.module_ |> ReasonReact.string}
            </dd>
          </div>
          <div className=Styles.name>
            <dt className=Styles.term>
              {L10N.Summary.name |> ReasonReact.string}
            </dt>
            <dd className=Styles.definition>
              {data |> Mapper.getName |> ReasonReact.string}
            </dd>
          </div>
          Rationale.Option.Infix.(
            <Tabs className=Styles.size selectedIndex=1>
              {originalSize
               <$> renderSize(L10N.Summary.original)
               |> Utils.defaultTo(ReasonReact.null)}
              {renderSize(L10N.Summary.stat, statSize)}
              {parsedSize
               <$> renderSize(L10N.Summary.parsed)
               |> Utils.defaultTo(ReasonReact.null)}
            </Tabs>
          )
        </dl>
      </header>
      <div className=Styles.content> {data |> Mapper.getSource} modules </div>
    </div>;
  },
};