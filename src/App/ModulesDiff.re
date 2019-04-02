let renderFilenames = (filenames) => <>
  {ReasonReact.string(L10N.assets ++ ": ")}
  {switch (filenames) {
  | [a] => ReasonReact.string(a);
  | [_, b] => ReasonReact.string(b ++ {j|❗|j});
  | _ => ReasonReact.null
  }}
</>;

type props = {
  after: int,
  before: int,
  name: string,
  module_: Compare.Modules.module_
};

let component = ReasonReact.statelessComponent("ModulesDiff");

let make = (~title, ~modules, ~onModule, _children) => {
  ...component,
  render: _self => switch (modules) {
  | [] => ReasonReact.null
  | _ => <>
    <h3>{ReasonReact.string(title)}</h3>
    <ul>
      ...(modules |> List.map(({
        after,
        before,
        module_,
        name,
      }) => {
        <li onClick=((_) => onModule(module_))>
          <strong>{ReasonReact.string(name)}</strong>
          <br/>
          <NumericDiff
            after=after
            before=before
          />
        </li>
      }) |> Array.of_list)
    </ul>
  </>
  }
};
