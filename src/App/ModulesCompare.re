// TODO: unify with ChunksCompare

open Compare.Modules;
open CompareKind;
open State.NavigationPath;

let component = ReasonReact.statelessComponent("ModulesCompare");

let getSummarySize = (m: Summary.t) =>
  switch (m.parsedSize) {
  | Some(size) => size
  | None => m.size
  };

let getModifiedSummarySize = (m: ModifiedSummary.t(Compare.Modules.t)) =>
  switch (m.parsedSize) {
  | Some(size) => size
  | None => m.size
  };

let mapModulesToProps = (modules, onModule) => {
  let added =
    modules.added
    |> List.map((module_: Summary.t) =>
         (
           {
             after: module_ |> getSummarySize,
             before: 0,
             name: module_.name,
             value: Summary(module_),
             onChange: module_ => {
               onModule(Segment.of_module(Added, module_));
               ();
             },
           }: ModulesDiff.props
         )
       );
  let removed =
    modules.removed
    |> List.map((module_: Summary.t) =>
         (
           {
             after: 0,
             before: module_ |> getSummarySize,
             name: module_.name,
             value: Summary(module_),
             onChange: module_ => {
               onModule(Segment.of_module(Removed, module_));
               ();
             },
           }: ModulesDiff.props
         )
       );
  let intact =
    modules.intact
    |> List.map((module_: Summary.t) => {
         let size = module_ |> getSummarySize;
         (
           {
             after: size,
             before: size,
             name: module_.name,
             value: Summary(module_),
             onChange: module_ => {
               onModule(Segment.of_module(Intact, module_));
               ();
             },
           }: ModulesDiff.props
         );
       });
  let modified =
    modules.modified
    |> List.map((module_: ModifiedSummary.t(Compare.Modules.t)) => {
         let size = module_ |> getModifiedSummarySize;
         (
           {
             after: size |> snd,
             before: size |> fst,
             name: module_.name,
             value: ModifiedSummary(module_),
             onChange: module_ => {
               onModule(Segment.of_module(Modified, module_));
               ();
             },
           }: ModulesDiff.props
         );
       });

  // TODO: test
  Belt.List.concatMany([|added, modified, removed, intact|]);
};

let make = (~modules, ~onModule, ~selected, ~className="", _children) => {
  ...component,
  render: _self =>
    <ModulesDiff
      className
      data={mapModulesToProps(modules, onModule)}
      selected
    />,
};