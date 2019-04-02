open Compare.Modules.Summary;

let component = ReasonReact.statelessComponent("ModulesList");

let make = (~modules, ~onModule, _children) => {
  ...component,
  render: _self => <>
    <h3>{ReasonReact.string(L10N.modules)}</h3>
    <ul>...(modules |> List.map(({
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
          ? <>
              <h4>{L10N.submodules |> ReasonReact.string}</h4>
              <ul>...(modules |> List.map((module_) => (
                <li onClick=((_) => onModule(module_))>
                  {module_.name |> ReasonReact.string}
                </li>)) |> Array.of_list)
              </ul>
            </>
          : ReasonReact.null}
      </li>
    }) |> Array.of_list)
    </ul>
  </>
};
