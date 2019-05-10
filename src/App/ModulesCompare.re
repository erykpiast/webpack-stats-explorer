// TODO: unify with ChunksCompare

open Compare.Modules;
open Compare.Kind;
open State.NavigationPath;

let component = ReasonReact.statelessComponent("ChunksCompare");

let mapModulesToProps = (modules, onModule) => {
  let added =
    modules.added
    |> List.map((module_: Summary.t) =>
         ModulesDiff.{
           after: module_.size,
           before: 0,
           name: module_.name,
           module_: Summary(module_),
           onModule: module_ => {
             onModule(Segment.of_module(Added, module_));
             ();
           },
         }
       );
  let removed =
    modules.removed
    |> List.map((module_: Summary.t) =>
         ModulesDiff.{
           after: 0,
           before: module_.size,
           name: module_.name,
           module_: Summary(module_),
           onModule: module_ => {
             onModule(Segment.of_module(Removed, module_));
             ();
           },
         }
       );
  let intact =
    modules.intact
    |> List.map((module_: Summary.t) =>
         ModulesDiff.{
           after: module_.size,
           before: module_.size,
           name: module_.name,
           module_: Summary(module_),
           onModule: module_ => {
             onModule(Segment.of_module(Intact, module_));
             ();
           },
         }
       );
  let modified =
    modules.modified
    |> List.map((module_: ModifiedSummary.t(Compare.Modules.t)) =>
         ModulesDiff.{
           after: snd(module_.size),
           before: fst(module_.size),
           name: module_.name,
           module_: ModifiedSummary(module_),
           onModule: module_ => {
             onModule(Segment.of_module(Modified, module_));
             ();
           },
         }
       );

  // TODO: test
  Belt.List.concatMany([|added, modified, removed, intact|])
  |> List.sort(
       ModulesDiff.(
         (a, b) => {
           let aDiff = a.after - a.before;
           let bDiff = b.after - b.before;
           let diffOfDiffs = bDiff - aDiff;

           if (diffOfDiffs === 0) {
             0;
           } else if (aDiff === 0) {
             1;
           } else if (bDiff === 0) {
             (-1);
           } else {
             diffOfDiffs;
           };
         }
       ),
     );
};

let make = (~modules, ~onModule, ~className="", _children) => {
  ...component,
  render: _self =>
    <ModulesDiff className modules={mapModulesToProps(modules, onModule)} />,
};