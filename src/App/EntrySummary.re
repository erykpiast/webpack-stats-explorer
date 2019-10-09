open CompareEntry;
open CompareKind;
open Rationale.Option.Infix;

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

  let size = style([marginTop(Theme.Space.default)]);

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

let getKindProps = kind =>
  switch (kind) {
  | Added => (Styles.Kind.added, L10N.Kind.added)
  | Removed => (Styles.Kind.removed, L10N.Kind.removed)
  | Intact => (Styles.Kind.intact, L10N.Kind.intact)
  | Modified => (Styles.Kind.modified, L10N.Kind.modified)
  };

let makeEntryData = data => EntryData(data);
let makeModifiedEntryData = data => ModifiedEntryData(data);

let getId = entry =>
  switch (entry) {
  | Entry(entry) => entry.id
  | ModifiedEntry(entry) => entry.id
  };
let getModules = entry =>
  switch (entry) {
  | Entry(entry) => NotModifiedChildren(entry.children)
  | ModifiedEntry(entry) => ModifiedChildren(entry.children)
  };
let getStat = entry =>
  switch (entry) {
  | Entry(entry) => entry.stat <$> makeEntryData
  | ModifiedEntry(entry) => entry.stat <$> makeModifiedEntryData
  };
let getOriginal = entry =>
  switch (entry) {
  | Entry(entry) => entry.original <$> makeEntryData
  | ModifiedEntry(entry) => entry.original <$> makeModifiedEntryData
  };
let getParsed = entry =>
  switch (entry) {
  | Entry(entry) => entry.parsed <$> makeEntryData
  | ModifiedEntry(entry) => entry.parsed <$> makeModifiedEntryData
  };

let renderModules = (onEntry, kind, selected, modules) =>
  switch (modules) {
  | NotModifiedChildren(entries) =>
    <EntryList
      className=Styles.modules
      entries
      kind
      onEntry
      selected={selected <$> getId}
    />
  | ModifiedChildren(entries) =>
    <EntryCompare
      className=Styles.modules
      entries
      onEntry
      selected={selected <$> getId}
    />
  };
let renderSize = (label, data) =>
  switch (data) {
  | None => ReasonReact.null
  | Some(data) =>
    let size =
      switch (data) {
      | EntryData({size}) => size
      | ModifiedEntryData({size}) => size |> snd
      };
    let diff =
      switch (data) {
      | EntryData({size}) => ReasonReact.null
      | ModifiedEntryData({size}) =>
        <>
          {nbsp |> ReasonReact.string}
          <NumericDiff before={size |> fst} after={size |> snd} />
        </>
      };

    <>
      <dt className={Cn.make([Styles.term, Styles.sizeTerm])}>
        {label |> ReasonReact.string}
      </dt>
      <dd className=Styles.definition> <Size value=size /> diff </dd>
    </>;
  };
let renderSource = data =>
  switch (data) {
  | None => ReasonReact.null
  | Some(data) =>
    switch (data) {
    | EntryData({source}) =>
      <pre className=Styles.code> {source |> ReasonReact.string} </pre>
    | ModifiedEntryData({source}) =>
      <CodeDiff
        className=Styles.code
        before={source |> fst}
        after={source |> snd}
      />
    }
  };

type action =
  | SwitchTab(int);

type state = {currentTabIndex: int};

let reducer = (action, _state) =>
  switch (action) {
  | SwitchTab(index) => ReasonReact.Update({currentTabIndex: index})
  };

let component = ReasonReact.reducerComponent("EntrySummary");

let make = (~entry, ~kind, ~onEntry, ~selected, _children) => {
  ...component,
  reducer,
  initialState: () => {currentTabIndex: 1},
  render: self => {
    let original = entry |> getOriginal;
    let stat = entry |> getStat;
    let parsed = entry |> getParsed;
    let currentData =
      switch (self.state.currentTabIndex) {
      | 0 => original
      | 2 => parsed
      | _ => stat
      };
    let (kindClassName, kindLabel) = getKindProps(kind);

    <div className=Styles.wrapper>
      <header className=Styles.header>
        <dl className=Styles.list>
          <div className=Styles.status>
            <dt className=Styles.term>
              {L10N.Summary.status |> ReasonReact.string}
            </dt>
            <dd className={Cn.make([Styles.definition, kindClassName])}>
              {kindLabel |> ReasonReact.string}
              {nbsp |> ReasonReact.string}
              {L10N.module_ |> ReasonReact.string}
            </dd>
          </div>
          <div className=Styles.name>
            <dt className=Styles.term>
              {L10N.Summary.name |> ReasonReact.string}
            </dt>
            <dd className=Styles.definition>
              {entry |> getId |> ReasonReact.string}
            </dd>
          </div>
          <Tabs
            className=Styles.size
            selectedIndex={self.state.currentTabIndex}
            onChange={index => self.send(SwitchTab(index))}>
            {original |> renderSize(L10N.Summary.original)}
            {stat |> renderSize(L10N.Summary.stat)}
            {parsed |> renderSize(L10N.Summary.parsed)}
          </Tabs>
        </dl>
      </header>
      <div className=Styles.content>
        {currentData |> renderSource}
        {entry |> getModules |> renderModules(onEntry, kind, selected)}
      </div>
    </div>;
  },
};