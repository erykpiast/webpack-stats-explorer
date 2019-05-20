open State.NavigationPath;

module type Interface = {
  type a;

  let componentName: string;
  let getName: a => string;
  let getSize: a => int;
  let getSource: a => ReasonReact.reactElement;
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
      padding(Theme.Space.double),
      flexGrow(0.0),
      borderBottom(px(1), `solid, Theme.Color.Border.default),
    ]);

  let modules =
    style([
      backgroundColor(Theme.Color.Background.default),
      width(Theme.Space.triplehexfold),
      marginLeft(`auto),
      height(`percent(100.0)),
      padding(Theme.Space.default),
    ]);

  let status = style([textTransform(`uppercase)]);

  let name = style([fontSize(rem(2.0))]);
  let size = style([fontSize(rem(1.2))]);

  let content = style([display(`flex), flexGrow(1.0)]);

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

  let make = (~data, ~kind, ~onModule, _children) => {
    ...component,
    render: _self =>
      <div className=Styles.wrapper>
        <header className=Styles.header>
          <dl className=Styles.list>
            <div className=Styles.status>
              <dt className=Styles.term>
                {L10N.Chunk.status |> ReasonReact.string}
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
                {L10N.Chunk.name |> ReasonReact.string}
              </dt>
              <dd className=Styles.definition>
                {data |> ToSummarize.getName |> ReasonReact.string}
              </dd>
            </div>
            <div className=Styles.size>
              <dt className=Styles.term>
                {L10N.Chunk.size |> ReasonReact.string}
              </dt>
              <dd className=Styles.definition>
                <Size value={data |> ToSummarize.getSize} />
              </dd>
            </div>
          </dl>
        </header>
        <div className=Styles.content>
          {data |> ToSummarize.getSource}
          {switch (ToSummarize.getModules(data)) {
           | Some(modules) =>
             switch (modules) {
             | NotModifiedModules(modules) =>
               <ModulesList className=Styles.modules modules kind onModule />
             | ModifiedModules(modules) =>
               <ModulesCompare className=Styles.modules modules onModule />
             }
           | None => ReasonReact.null
           }}
        </div>
      </div>,
  };
};