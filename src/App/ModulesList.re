open Compare.Modules.Summary;

module Styles = {
  open Css;

  let list = style([listStyleType(`none)]);
};

let component = ReasonReact.statelessComponent("ModulesList");

let make = (~modules, ~onModule, _children) => {
  ...component,
  render: _self =>
    switch (modules) {
    | [] => ReasonReact.null
    | modules =>
      <>
        <h3> {L10N.modules |> ReasonReact.string} </h3>
        <ul className=Styles.list>
          ...{
               modules
               |> List.map(module_ =>
                    <li onClick={_ => onModule(module_)}>
                      <strong> {module_.name |> ReasonReact.string} </strong>
                      {" " |> ReasonReact.string}
                      <Size value={module_.size} />
                    </li>
                  )
               |> Array.of_list
             }
        </ul>
      </>
    },
};