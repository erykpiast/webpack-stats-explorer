module type Interface = {
  type a;

  let componentName: string;
  let getName: a => string;
  let getSize: a => int;
  let getStatSize: a => int;
  let getOriginalSize: a => option(int);
  let getParsedSize: a => option(int);
  let getSource: a => ReasonReact.reactElement;
  let getOriginalSource: a => option(ReasonReact.reactElement);
  let getParsedSource: a => option(ReasonReact.reactElement);
  let getModules: a => option(Compare.Modules.modules);
};

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

  module Kind = {
    let added = style([color(Theme.Color.Added.default)]);
    let removed = style([color(Theme.Color.Removed.default)]);
    let intact = style([color(Theme.Color.Intact.default)]);
    let modified = style([color(Theme.Color.Modified.default)]);
  };
};

let nbsp = {js|  |js};

let getKindMessage =
  Compare.Kind.(
    kind =>
      switch (kind) {
      | Added => L10N.Kind.added
      | Removed => L10N.Kind.removed
      | Intact => L10N.Kind.intact
      | Modified => L10N.Kind.modified
      }
  );

let getKindClassName =
  Compare.Kind.(
    kind =>
      switch (kind) {
      | Added => Styles.Kind.added
      | Removed => Styles.Kind.removed
      | Intact => Styles.Kind.intact
      | Modified => Styles.Kind.modified
      }
  );

module Make = (ToSummarize: Interface) => {
  let component = ReasonReact.statelessComponent(ToSummarize.componentName);

  let make = (~data, ~kind, ~onModule, ~selected, _children) => {
    ...component,
    render: _self => {
      let ownSize = data |> ToSummarize.getStatSize;
      let statSize = data |> ToSummarize.getSize;
      let originalSize = data |> ToSummarize.getOriginalSize;
      let parsedSize = data |> ToSummarize.getParsedSize;

      let (modules, modulesCount) =
        switch (data |> ToSummarize.getModules) {
        | Some(modules) =>
          Rationale.Option.Infix.(
            switch (modules) {
            | NotModifiedModules(modules) => (
                <ModulesList
                  className=Styles.modules
                  modules
                  kind
                  onModule
                  selected={selected <$> ToSummarize.getName}
                />,
                modules |> List.length,
              )
            | ModifiedModules(modules) => (
                <ModulesCompare
                  className=Styles.modules
                  modules
                  onModule
                  selected={selected <$> ToSummarize.getName}
                />,
                modules |> Compare.Modules.count |> snd,
              )
            }
          )
        | None => (ReasonReact.null, 0)
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
                {data |> ToSummarize.getName |> ReasonReact.string}
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
        <div className=Styles.content>
          {data |> ToSummarize.getSource}
          modules
        </div>
      </div>;
    },
  };
};