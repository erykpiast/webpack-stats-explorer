open Compare.Modules;

module type ModulesCompare = {
  let make: (
    ~modules: modules,
    ~onModule: (module_) => unit,
    ~title: string,
    'a
  ) => ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless
  )
};

module rec ModulesCompare: ModulesCompare = {

  let component = ReasonReact.statelessComponent("ModulesCompare");

  let make = (~modules, ~onModule, ~title, _children) => {
    ...component,
    render: _self => switch modules {
      | NotModifiedModules(modules) => switch modules {
        | [] => ReasonReact.null
        | modules => {
          let rec mapNotModifiedModules = (modules) => modules
            |> List.map((m: Compare.Modules.Summary.t) => ModulesList.({
              name: m.name,
              size: m.size,
              source: m.source,
              modules: m.modules |> mapNotModifiedModules
            }));

          <ModulesList
            title={title}
            modules={modules |> mapNotModifiedModules}
          />
        }}
      | ModifiedModules(diff) => <>
        <h3>{ReasonReact.string(title)}</h3>
        <ModulesCompare
          modules={NotModifiedModules(diff.added)}
          onModule={onModule}
          title={L10N.added}
        />
        <ModulesCompare
          modules={NotModifiedModules(diff.removed)}
          onModule={onModule}
          title={L10N.removed}
        />
        <ModulesCompare
          modules={NotModifiedModules(diff.intact)}
          onModule={onModule}
          title={L10N.intact}
        />
        {switch (diff.modified) {
        | [] => ReasonReact.null
        | modified => <>
          <h3>{ReasonReact.string(L10N.modified)}</h3>
          <ul>...(modified |> List.map((module_: ModifiedSummary.t(t)) => {
            <li>
              <strong>{ReasonReact.string(module_.name)}</strong>
              <br/>
              <NumericDiff
                after={snd(module_.size)}
                before={fst(module_.size)}
              />
              <br/>
              <CodeDiff
                before={fst(module_.source)}
                after={snd(module_.source)}
              />
              {switch module_.modules {
              | None => ReasonReact.null
              | Some(submodules) => <ModulesCompare
                modules={ModifiedModules(submodules)}
                onModule={onModule}
                title={L10N.submodules}
              />
              }}
            </li>
          }) |> Array.of_list)
          </ul>
          </>
        }}
      </>
    }
  };
};

let make = ModulesCompare.make;
