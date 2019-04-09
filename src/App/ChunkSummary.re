open Compare.Chunks;
open State.NavigationPath;

let getModules = chunk =>
  switch (chunk) {
  | Summary(chunk) => Compare.Modules.NotModifiedModules(chunk.modules)
  | ModifiedSummary(chunk) => Compare.Modules.ModifiedModules(chunk.modules)
  };

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

module Styles = {
  open Css;

  let term = style([fontWeight(`bold)]);

  let definition = style([]);
};

let component = ReasonReact.statelessComponent("ChunkSummary");

let make = (~chunk, ~kind, ~onModule, _children) => {
  ...component,
  render: _self =>
    <>
      <header>
        <dl>
          <dt className=Styles.term>
            {L10N.Chunk.status |> ReasonReact.string}
          </dt>
          <dd className=Styles.definition>
            {kind |> getKindMessage |> ReasonReact.string}
          </dd>
          <dt className=Styles.term>
            {L10N.Chunk.name |> ReasonReact.string}
          </dt>
          <dd className=Styles.definition>
            {chunk |> getName |> ReasonReact.string}
          </dd>
          <dt className=Styles.term>
            {L10N.Chunk.size |> ReasonReact.string}
          </dt>
          <dd className=Styles.definition>
            <Size value={chunk |> getSize} />
          </dd>
        </dl>
      </header>
      {switch (getModules(chunk)) {
       | NotModifiedModules(modules) =>
         <ModulesList
           modules
           onModule={module_ =>
             Compare.Modules.Summary(module_)
             |> Segment.of_module(kind)
             |> onModule
           }
         />
       | ModifiedModules(modules) => <ModulesCompare modules onModule />
       }}
    </>,
};