open Compare.Modules.Summary;

module Styles = {
  open Css;

  let list =
    style([listStyleType(`none), padding(px(0)), margin(px(0))]);

  let item =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      marginBottom(Theme.Space.double),
      marginTop(Theme.Space.double),
    ]);
};

let component = ReasonReact.statelessComponent("ModulesList");

let make = (~modules, ~onModule, ~className="", _children) => {
  ...component,
  render: _self =>
    switch (modules) {
    | [] => ReasonReact.null
    | modules =>
      <ul className=Cn.make([Styles.list, className])>
        ...{
             modules
             |> List.map(module_ =>
                  <li onClick={_ => onModule(module_)} className=Styles.item>
                    <strong> {module_.name |> ReasonReact.string} </strong>
                    {" " |> ReasonReact.string}
                    <Size value={module_.size} />
                  </li>
                )
             |> Array.of_list
           }
      </ul>
    },
};