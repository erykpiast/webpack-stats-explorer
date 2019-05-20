open Compare.Kind;
open Compare.Modules.Summary;
open State.NavigationPath;

let mapModulesToProps = (modules, kind, onModule) => {
  modules
  |> List.map(module_ => {
       let [after, before] =
         switch (kind) {
         | Added => [module_.size, 0]
         | Removed => [0, module_.size]
         | Intact => [module_.size, module_.size]
         | Modified => [0, 0]
         };

       (
         {
           after,
           before,
           name: module_.name,
           value: Summary(module_),
           onChange: module_ => {
             onModule(Segment.of_module(kind, module_));
             ();
           },
         }: ModulesDiff.props
       );
     });
};

let component = ReasonReact.statelessComponent("ModulesList");

let make = (~modules, ~onModule, ~kind, ~className="", _children) => {
  ...component,
  render: _self =>
    <ModulesDiff
      className
      data={mapModulesToProps(modules, kind, onModule)}
    />,
};