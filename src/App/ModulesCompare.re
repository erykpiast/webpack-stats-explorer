open Compare.Modules;
open Compare.Kind;
open State.NavigationPath;

let component = ReasonReact.statelessComponent("ChunksCompare");

let make = (~modules, ~onModule, _children) => {
  let renderModulesDiff = (mapper, title, onModule, modules) => <ModulesDiff
    modules=(modules |> List.map(mapper))
    title=title
    onModule=onModule
  />;
  {
    ...component,
    render: _self => {
      let added = renderModulesDiff(
        (module_: Summary.t) => {
          after: module_.size,
          before: 0,
          name: module_.name,
          module_: Summary(module_)
        },
        L10N.added,
        (module_) => onModule(Segment.of_module(Added, module_)), modules.added);
      let removed = renderModulesDiff(
        (module_: Summary.t) => {
          after: 0,
          before: module_.size,
          name: module_.name,
          module_: Summary(module_)
        },
        L10N.removed,
        (module_) => onModule(Segment.of_module(Removed, module_)), modules.removed);
      let intact = renderModulesDiff(
        (module_: Summary.t) => {
          after: module_.size,
          before: module_.size,
          name: module_.name,
          module_: Summary(module_)
        },
        L10N.intact,
        (module_) => onModule(Segment.of_module(Intact, module_)), modules.intact);
      let modified = renderModulesDiff(
        (module_: ModifiedSummary.t(Compare.Modules.t)) => {
          after: snd(module_.size),
          before: fst(module_.size),
          name: module_.name,
          module_: ModifiedSummary(module_)
        },
        L10N.modified,
        (module_) => onModule(Segment.of_module(Modified, module_)), modules.modified);
      <>
        <h3>{ReasonReact.string(L10N.modules)}</h3>
        {added}
        {removed}
        {intact}
        {modified}
      </>
    }
  };
};