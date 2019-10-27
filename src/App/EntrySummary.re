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
      width(Theme.Space.triplehexteenfold),
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

  let code = style([padding(Theme.Space.default)]);

  module Kind = {
    let added = style([color(Theme.Color.Added.default)]);
    let removed = style([color(Theme.Color.Removed.default)]);
    let intact = style([color(Theme.Color.Intact.default)]);
    let modified = style([color(Theme.Color.Modified.default)]);
  };

  module PluginBait = {
    let root =
      style([
        display(`flex),
        flexDirection(`column),
        flexGrow(1.0),
        justifyContent(`center),
        alignItems(`center),
      ]);

    let heading = style([fontSize(Theme.Space.triple)]);

    let caption = style([]);

    let snippet =
      style([
        backgroundColor(Theme.Color.Background.default),
        padding(Theme.Space.default),
      ]);

    let prompt = style([userSelect(`none)]);
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

let renderSize = (label, data) =>
  switch (data) {
  | None => <> {label |> React.string} </>
  | Some(data) =>
    let size =
      switch (data) {
      | EntryData({size}) => size
      | ModifiedEntryData({size}) => size |> snd
      };
    let diff =
      switch (data) {
      | EntryData(_) => ReasonReact.null
      | ModifiedEntryData({size}) =>
        <>
          {nbsp |> React.string}
          <NumericDiff before={size |> fst} after={size |> snd} />
        </>
      };

    <>
      <dt className={Cn.make([Styles.term, Styles.sizeTerm])}>
        {label |> React.string}
      </dt>
      <dd className=Styles.definition> <Size value=size /> diff </dd>
    </>;
  };
let renderSource = data =>
  switch (data) {
  | None =>
    // NOTE: there are some cases when plugin is configured but some
    // enhanced source is not available
    // TODO: detect plugin based on whole stats object
    <div className=Styles.PluginBait.root>
      <h3 className=Styles.PluginBait.heading>
        {"No code here?" |> React.string}
      </h3>
      <p className=Styles.PluginBait.caption>
        {"Add " |> React.string}
        <a
          href="https://www.npmjs.com/package/webpack-enhanced-stats-plugin"
          target="_blank">
          {"webpack-enhanced-stats-plugin" |> React.string}
        </a>
        {" to your Webpack config!" |> React.string}
      </p>
      <pre className=Styles.PluginBait.snippet>
        <span className=Styles.PluginBait.prompt>
          {"$ " |> React.string}
        </span>
        <code>
          {"npm i -D webpack-enhanced-stats-plugin" |> React.string}
        </code>
      </pre>
      <pre className=Styles.PluginBait.snippet>
        <code>
          {"const StatsPlugin = require(\"webpack-enhanced-stats-plugin\");

module.exports = {
  // set any source-map devtool (not none/false nor eval)
  devtool: 'source-map',
  module: {
    rules: [
      // other loaders here, this has to be the last one
      {
        loader: StatsPlugin.loader
      }
    ]
  },
  plugins: [
    // write out stats file to the output directory
    new StatsPlugin({
      filename: 'stats.json'
    })
  ]
}"
           |> React.string}
        </code>
      </pre>
    </div>
  | Some(data) =>
    switch (data) {
    | EntryData({source}) => <Code className=Styles.code> ...source </Code>
    | ModifiedEntryData({source}) =>
      let before = source |> fst;
      let after = source |> snd;

      if (after == before) {
        <Code className=Styles.code> ...after </Code>;
      } else {
        <CodeDiff className=Styles.code before after />;
      };
    }
  };

[@react.component]
let make = (~entry, ~kind) => {
  let (index, setIndex) = React.useState(() => 1);

  let original = entry |> getOriginal;
  let stat = entry |> getStat;
  let parsed = entry |> getParsed;
  let currentData =
    switch (index) {
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
            {L10N.Summary.status |> React.string}
          </dt>
          <dd className={Cn.make([Styles.definition, kindClassName])}>
            {kindLabel |> React.string}
            {nbsp |> React.string}
            {L10N.module_ |> React.string}
          </dd>
        </div>
        <div className=Styles.name>
          <dt className=Styles.term> {L10N.Summary.name |> React.string} </dt>
          <dd className=Styles.definition>
            {entry |> getId |> React.string}
          </dd>
        </div>
        <Tabs
          className=Styles.size
          selectedIndex=index
          onChange={index => setIndex(_ => index)}>
          [|
            original |> renderSize(L10N.Summary.original),
            stat |> renderSize(L10N.Summary.stat),
            parsed |> renderSize(L10N.Summary.parsed),
          |]
        </Tabs>
      </dl>
    </header>
    <div className=Styles.content> {currentData |> renderSource} </div>
  </div>;
};