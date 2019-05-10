open Compare.Chunks;
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
      flexGrow(1.0),
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

  module Kind = {
    let added = style([color(Theme.Color.Added.default)]);
    let removed = style([color(Theme.Color.Removed.default)]);
    let intact = style([color(Theme.Color.Intact.default)]);
    let modified = style([color(Theme.Color.Modified.default)]);
  };
};

let nbsp = {js|  |js};
let getName = chunk =>
  switch (chunk) {
  | Summary(chunk) => chunk.name
  | ModifiedSummary(chunk) => chunk.name
  };

let getSize = chunk =>
  switch (chunk) {
  | Summary(chunk) => chunk.size
  | ModifiedSummary(chunk) => fst(chunk.size)
  };

let getModules = chunk =>
  switch (chunk) {
  | Summary(chunk) => Compare.Modules.NotModifiedModules(chunk.modules)
  | ModifiedSummary(chunk) => Compare.Modules.ModifiedModules(chunk.modules)
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

let component = ReasonReact.statelessComponent("ChunkSummary");

let make = (~chunk, ~kind, ~onModule, _children) => {
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
              {L10N.chunk |> ReasonReact.string}
            </dd>
          </div>
          <div className=Styles.name>
            <dt className=Styles.term>
              {L10N.Chunk.name |> ReasonReact.string}
            </dt>
            <dd className=Styles.definition>
              {chunk |> getName |> ReasonReact.string}
            </dd>
          </div>
          <div className=Styles.size>
            <dt className=Styles.term>
              {L10N.Chunk.size |> ReasonReact.string}
            </dt>
            <dd className=Styles.definition>
              <Size value={chunk |> getSize} />
            </dd>
          </div>
        </dl>
      </header>
      {switch (getModules(chunk)) {
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
       }}
    </div>,
};