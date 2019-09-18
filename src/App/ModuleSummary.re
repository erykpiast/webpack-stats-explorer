module Styles = {
  open Css;

  let code =
    style([
      padding(Theme.Space.default),
      whiteSpace(`preWrap),
      wordBreak(`breakAll),
    ]);
};

module ModuleSummary =
  GenericSummary.Make({
    open Compare.Modules;
    open Rationale.Option.Infix;

    type a = module_;

    let componentName = "ModuleSummary";
    let getName = module_ =>
      switch (module_) {
      | Summary(module_) => module_.name
      | ModifiedSummary(module_) => module_.name
      };
    let getSize = module_ =>
      switch (module_) {
      | Summary(module_) => module_.size
      | ModifiedSummary(module_) => module_.size |> snd
      };
    let getStatSize = module_ =>
      switch (module_) {
      | Summary(module_) => module_.ownSize
      | ModifiedSummary(module_) => module_.ownSize |> snd
      };
    let getOriginalSize = module_ =>
      switch (module_) {
      | Summary(module_) => module_.originalSize
      | ModifiedSummary(module_) => module_.originalSize <$> snd
      };
    let getParsedSize = module_ =>
      switch (module_) {
      | Summary(module_) => module_.parsedSize
      | ModifiedSummary(module_) => module_.parsedSize <$> snd
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
          code =>
            <pre className=Styles.code> {code |> ReasonReact.string} </pre>
        )
      | ModifiedSummary(module_) =>
        <CodeDiff
          className=Styles.code
          before={fst(module_.source)}
          after={snd(module_.source)}
        />
      };
    let getOriginalSource = _ => None;
    let getParsedSource = _ => None;
    let getModules = module_ =>
      switch (module_) {
      | Summary(module_) =>
        let modules =
          if (String.length(module_.source) > 0) {
            module_.modules;
          } else if (List.length(module_.modules) > 0) {
            List.tl(module_.modules);
          } else {
            [];
          };
        Some(Compare.Modules.NotModifiedModules(modules));
      | ModifiedSummary(module_) =>
        switch (module_.modules) {
        | Some(modules) => Some(Compare.Modules.ModifiedModules(modules))
        | None => None
        }
      };
  });

let make = ModuleSummary.make;