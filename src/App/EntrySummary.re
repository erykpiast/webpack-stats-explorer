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
  let sizeTermWrapper = style([width(`percent(100.0))]);
  let sizeTerm = style([display(`block), marginRight(Theme.Space.default)]);
  let content =
    style([
      display(`flex),
      flexGrow(1.0),
      minHeight(px(0)),
      position(`relative),
      overflow(`scroll),
    ]);
  let code = style([padding(Theme.Space.default), width(`percent(100.0))]);

  let tabsPlaceholder = style([height(Theme.Space.default)]);

  let diffSwitch = style([marginLeft(`auto)]);

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

  module ViewSettings = {
    let wrapper =
      style([
        background(Theme.Color.Background.default),
        display(`flex),
        alignItems(`center),
        padding(Theme.Space.default),
        fontSize(Theme.Size.Text.button),
        lineHeight(Theme.Size.LineHeight.default),
      ]);

    let label = style([marginRight(Theme.Space.default)]);
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

let getSize = entry =>
  switch (entry) {
  | Entry(entry) => (entry.size, entry.size)
  | ModifiedEntry(entry) => entry.size
  };

let getChildrenCount = entry =>
  switch (entry) {
  | Entry(entry) => entry.children |> List.length
  | ModifiedEntry(entry) => entry.children |> CompareEntry.count |> snd
  };

let getLanguage = id => {
  let extension =
    id
    |> Utils.String.split(".")
    |> Utils.Array.reverse
    |> Utils.Array.nth(0);

  switch (extension) {
  | "json" => `Json
  | "css" => `Css
  | "pcss" => `Css
  | "scss" => `Scss
  | "ts" => `TypeScript
  | "tsx" => `TypeScript
  | _ => `JavaScript
  };
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

    <div className={Styles.sizeTermWrapper} id={"entry-size-" ++ (label |> String.uncapitalize_ascii)}>
      <dt className={Cn.fromList([Styles.term, Styles.sizeTerm])}>
        {label |> React.string}
      </dt>
      <dd className=Styles.definition> <Size value=size /> diff </dd>
    </div>;
  };
let renderSource = (~formatter, ~columnGuideline, ~language, ~diffMode, data) =>
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
    | EntryData({source}) =>
      <Code className=Styles.code columnGuideline language>
        ...{source |> formatter}
      </Code>
    | ModifiedEntryData({source}) =>
      let before = source |> fst |> formatter;
      let after = source |> snd |> formatter;

      if (after == before) {
        <Code className=Styles.code columnGuideline language> ...after </Code>;
      } else {
        <CodeDiff columnGuideline before after language mode=diffMode />;
      };
    }
  };

let getDefaultFormattingForTab = (!==)(0);

let prettyPrintInputId = "pretty-print";
let lineWrapInputId = "line-wrap";

[@react.component]
let make = (~entry, ~onTab, ~tab, ~onDiffMode, ~diffMode, ~kind) => {
  let original = entry |> getOriginal;
  let stat = entry |> getStat;
  let parsed = entry |> getParsed;
  let id = entry |> getId;
  let (language, currentData) =
    switch (tab) {
    | 0 => (id |> getLanguage, original)
    | 2 => (`JavaScript, parsed)
    | _ => (`JavaScript, stat)
    };
  let (kindClassName, kindLabel) = getKindProps(kind);
  let (isPrettyPrintEnabled, setPrettyPrintEnabled) =
    React.useState(() => getDefaultFormattingForTab(tab));
  let (isLineWrappingEnabled, setLineWrappingEnabled) =
    React.useState(() => getDefaultFormattingForTab(tab));
  let switchTab = index => {
    let defaultFormatting = getDefaultFormattingForTab(index);
    setPrettyPrintEnabled(_ => defaultFormatting);
    setLineWrappingEnabled(_ => defaultFormatting);
    onTab(index);
  };
  let hardLineWrapLimit =
    CodeDiff.(
      switch (diffMode) {
      | Unified => 120
      | Split => 80
      }
    );
  let wrapLineLength = isLineWrappingEnabled ? hardLineWrapLimit : 0;
  let formatter =
    isPrettyPrintEnabled
      ? code =>
          JsBeautify.js(
            ~indent_size=2,
            ~wrap_line_length=wrapLineLength,
            code,
          )
      : Utils.identity;
  let columnGuideline =
    isPrettyPrintEnabled && isLineWrappingEnabled ? hardLineWrapLimit : 0;

  <div className=Styles.wrapper id="entry-overview">
    <header className=Styles.header>
      <dl className=Styles.list>
        <div className=Styles.status>
          <dt className=Styles.term>
            {L10N.Summary.status |> React.string}
          </dt>
          <dd className={Cn.fromList([Styles.definition, kindClassName])} id="entry-kind">
            {kindLabel |> React.string}
            {nbsp |> React.string}
            {L10N.module_ |> React.string}
          </dd>
        </div>
        <div className=Styles.name id="entry-name">
          <dt className=Styles.term> {L10N.Summary.name |> React.string} </dt>
          <dd className=Styles.definition> {id |> React.string} </dd>
        </div>
        {switch (original, stat, parsed) {
         | (None, None, None) => <div className=Styles.tabsPlaceholder />
         | _ =>
           <Tabs className=Styles.size selectedIndex=tab onChange=switchTab id="entry-sizes">
             [|
               original |> renderSize(L10N.Summary.original),
               stat |> renderSize(L10N.Summary.stat),
               parsed |> renderSize(L10N.Summary.parsed),
             |]
           </Tabs>
         }}
      </dl>
    </header>
    <div className=Styles.content id="entry-code">
      {switch (original, stat, parsed) {
       | (None, None, None) =>
         <EntryOverview
           size={entry |> getSize}
           level=`module_
           count={entry |> getChildrenCount}
           name={entry |> getId}
         />
       | _ =>
         currentData
         |> renderSource(~formatter, ~columnGuideline, ~language, ~diffMode)
       }}
    </div>
    <form className=Styles.ViewSettings.wrapper>
      <input
        type_="checkbox"
        id=prettyPrintInputId
        onChange={e => {
          let target = e |> ReactEvent.Form.target;
          setPrettyPrintEnabled(_ => target##checked);
        }}
        checked=isPrettyPrintEnabled
      />
      <label htmlFor=prettyPrintInputId className=Styles.ViewSettings.label>
        {L10N.prettyPrint |> React.string}
      </label>
      <input
        type_="checkbox"
        id=lineWrapInputId
        onChange={e => {
          let target = e |> ReactEvent.Form.target;
          setLineWrappingEnabled(_ => target##checked);
        }}
        checked={isPrettyPrintEnabled && isLineWrappingEnabled}
        disabled={!isPrettyPrintEnabled}
      />
      <label htmlFor=lineWrapInputId className=Styles.ViewSettings.label>
        {L10N.lineWrap |> React.string}
        {" (" |> React.string}
        {hardLineWrapLimit |> string_of_int |> React.string}
        {" " |> React.string}
        {L10N.columns |> React.string}
        {")" |> React.string}
      </label>
      {kind === Modified
         ? <DoubleSwitch
             className=Styles.diffSwitch
             onSwitch=onDiffMode
             current=diffMode
             a=(CodeDiff.Unified, "Unified")
             b=(CodeDiff.Split, "Split")
             id="diff-mode"
           />
         : React.null}
    </form>
  </div>;
};
