open Compare.Modules;

module ModulesDiff =
  GenericDiff.Make({
    type a = module_;

    let componentName = "ModulesDiff";
  });

let make = ModulesDiff.make;
type props = ModulesDiff.props;