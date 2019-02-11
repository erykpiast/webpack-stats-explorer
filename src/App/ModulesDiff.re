type props = {
  name: string,
  source: string,
};

let component = ReasonReact.statelessComponent("ModulesDiff");

let make = (~title, ~modules, _children) => {
  ...component,
  render: _self => <>
    <h3>{ReasonReact.string(title)}</h3>
    <ul>
      ...(modules |> List.map(({ name, source }) => {
        <li>
          <strong>{ReasonReact.string(name)}</strong>

        </li>
      }) |> Array.of_list)
    </ul>
  </>
};
