type m = {
  name: string,
  size: int,
  source: string,
  modules: list(m)
};

module type ModulesList = {
  let make: (
    ~title: string,
    ~modules: list(m),
    'a
  ) => ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless
  )
};

module rec ModulesList: ModulesList = {
  let component = ReasonReact.statelessComponent("ModulesList");

  let make = (~title, ~modules, _children) => {
    ...component,
    render: _self => <>
      <h3>{ReasonReact.string(title)}</h3>
      <ul>
        ...(modules |> List.map(({
          name,
          size,
          source,
          modules,
        }) => {
          <li>
            <strong>{ReasonReact.string(name)}</strong>
            <br />
            <Size value=size />
            <pre>{ReasonReact.string(source)}</pre>
            {List.length(modules) > 0
              ? <ModulesList
                title={L10N.submodules}
                modules={modules}
              />
              : ReasonReact.null}
          </li>
        }) |> Array.of_list)
      </ul>
    </>
  };
};

let make = ModulesList.make;
