module Styles = {
  open Css;

  let root =
    style([
      backgroundColor(Theme.Color.Background.bright),
      padding(Theme.Space.double),
    ]);
};

type payload = {
  name: string,
  color: string,
  value: float,
};

[@react.component]
let make = (~className="", ~payload: array('a), ~sizeUnit: Size.sizeUnit) => {
  <div className={Cn.fromList([className, Styles.root])}>
    {payload
     |> Array.map(({name, color, value}) =>
          if (value === 0.0) {
            React.null;
          } else {
            <div style={ReactDOMRe.Style.make(~color, ())} key=name>
              <strong> {name |> React.string} </strong>
              {": " |> React.string}
              {value |> int_of_float |> Size.displayValue(sizeUnit)}
              {" " |> React.string}
              {sizeUnit |> Size.displayUnit |> React.string}
            </div>;
          }
        )
     |> React.array}
  </div>;
};
