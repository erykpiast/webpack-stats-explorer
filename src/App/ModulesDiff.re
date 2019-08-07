open Compare.Modules;

module ModulesDiff =
  GenericDiff.Make({
    type a = module_;

    let componentName = "ModulesDiff";
    let getName = module_ =>
      switch (module_) {
      | Summary(module_) => module_.name
      | ModifiedSummary(module_) => module_.name
      };
  });

let make = ModulesDiff.make;
type props = ModulesDiff.props;