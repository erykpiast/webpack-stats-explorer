type m = {
  name: string,
  size: int,
  source: string,
};

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
      }) => {
        <li>
          <strong>{ReasonReact.string(name)}</strong>
          <br />
          <Size value=size />
          <pre>{ReasonReact.string(source)}</pre>
        </li>
      }) |> Array.of_list)
    </ul>
  </>
};
