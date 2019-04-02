open Compare.Modules;
open Compare.Kind;
open State.NavigationPath;

let getModules = (module_) => switch (module_) {
  | Summary(module_) => Some(Compare.Modules.NotModifiedModules(module_.modules))
  | ModifiedSummary(module_) => switch (module_.modules) {
    | Some(modules) => Some(Compare.Modules.ModifiedModules(modules))
    | None => None
  }
};

let getName = (module_) => switch (module_) {
  | Summary(module_) => module_.name
  | ModifiedSummary(module_) => module_.name
};

let getSize = (module_) => switch (module_) {
  | Summary(module_) => module_.size
  | ModifiedSummary(module_) => fst(module_.size)
};

let getSource = (module_) => switch (module_) {
  | Summary(module_) => module_.source
  | ModifiedSummary(module_) => fst(module_.source)
};

let getKindMessage = Compare.Kind.((kind) => switch (kind) {
  | Added => L10N.Kind.added
  | Removed => L10N.Kind.removed
  | Intact => L10N.Kind.intact
  | Modified => L10N.Kind.modified
});

module Styles = {
  open Css;

  let term = style([
    fontWeight(`bold)
  ]);

  let definition = style([]);
};

let component = ReasonReact.statelessComponent("ModuleSummary");

let make = (~module_, ~kind, ~onModule, _children) => {
  ...component,
  render: (_self) => <>
    <header>
      <dl>
        <dt className=Styles.term>{L10N.Module.status |> ReasonReact.string}</dt>
        <dd className=Styles.definition>{kind |> getKindMessage |> ReasonReact.string}</dd>

        <dt className=Styles.term>{L10N.Module.name |> ReasonReact.string}</dt>
        <dd className=Styles.definition>{module_ |> getName |> ReasonReact.string}</dd>

        <dt className=Styles.term>{L10N.Module.size |> ReasonReact.string}</dt>
        <dd className=Styles.definition>
          <Size value={module_ |> getSize} />
        </dd>

        <dt className=Styles.term>{L10N.Module.code |> ReasonReact.string}</dt>
        <dd className=Styles.definition>
          <pre>{module_ |> getSource |> ReasonReact.string}</pre>
        </dd>
      </dl>
    </header>
    (switch (getModules(module_)) {
    | Some(modules) => switch (modules) {
      | NotModifiedModules(modules) => <ModulesList
          modules=modules
          onModule=((module_) => Compare.Modules.Summary(module_)
            |> Segment.of_module(kind)
            |> onModule
          )
        />
      | ModifiedModules(modules) => <ModulesCompare
          modules=modules
          onModule=onModule
        />
      }
    | None => ReasonReact.null
    })
  </>
};