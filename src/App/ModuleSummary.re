open Compare.Modules;
open State.NavigationPath;

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
      width(Theme.Space.doublehexfold),
      marginLeft(`auto),
      height(`percent(100.0)),
      padding(Theme.Space.default),
    ]);

  let status = style([textTransform(`uppercase)]);

  let name = style([fontSize(rem(2.0))]);
  let size = style([fontSize(rem(1.2))]);

  let code = style([padding(Theme.Space.default)]);

  let content = style([display(`flex), flexGrow(1.0)]);

  module Kind = {
    let added = style([color(Theme.Color.Added.default)]);
    let removed = style([color(Theme.Color.Removed.default)]);
    let intact = style([color(Theme.Color.Intact.default)]);
    let modified = style([color(Theme.Color.Modified.default)]);
  };
};

let nbsp = {js|  |js};
let getName = module_ =>
  switch (module_) {
  | Summary(module_) => module_.name
  | ModifiedSummary(module_) => module_.name
  };

let getSize = module_ =>
  switch (module_) {
  | Summary(module_) => module_.size
  | ModifiedSummary(module_) => fst(module_.size)
  };

let getSource = module_ =>
  switch (module_) {
  | Summary(module_) =>
    {
      let source = module_.source;
      if (String.length(source) > 0) {
        source;
      } else if (List.length(module_.modules) > 0) {
        List.hd(module_.modules).source;
      } else {
        source;
      };
    }
    |> (
      code => <pre className=Styles.code> {code |> ReasonReact.string} </pre>
    )
  | ModifiedSummary(module_) =>
    <CodeDiff
      className=Styles.code
      before={fst(module_.source)}
      after={snd(module_.source)}
    />
  };

let getModules = module_ =>
  switch (module_) {
  | Summary(module_) =>
    let modules =
      if (String.length(module_.source) > 0) {
        module_.modules;
      } else {
        List.tl(module_.modules);
      };
    Some(Compare.Modules.NotModifiedModules(modules));
  | ModifiedSummary(module_) =>
    switch (module_.modules) {
    | Some(modules) => Some(Compare.Modules.ModifiedModules(modules))
    | None => None
    }
  };

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

let component = ReasonReact.statelessComponent("ModuleSummary");

let make = (~module_, ~kind, ~onModule, _children) => {
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
              {module_ |> getName |> ReasonReact.string}
            </dd>
          </div>
          <div className=Styles.size>
            <dt className=Styles.term>
              {L10N.Chunk.size |> ReasonReact.string}
            </dt>
            <dd className=Styles.definition>
              <Size value={module_ |> getSize} />
            </dd>
          </div>
        </dl>
      </header>
      <div className=Styles.content>
        {module_ |> getSource}
        {switch (getModules(module_)) {
         | Some(modules) =>
           switch (modules) {
           | NotModifiedModules(modules) =>
             <ModulesList
               className=Styles.modules
               modules
               onModule={module_ =>
                 Compare.Modules.Summary(module_)
                 |> Segment.of_module(kind)
                 |> onModule
               }
             />
           | ModifiedModules(modules) =>
             <ModulesCompare className=Styles.modules modules onModule />
           }
         | None => ReasonReact.null
         }}
      </div>
    </div>,
};