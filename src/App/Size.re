type unit =
  | B
  | KB
  | MB;

let displayValue = (value, unit) =>
  (
    switch (unit) {
    | B => value |> string_of_int
    | KB =>
      value
      |> float_of_int
      |> (x => x /. 1024.0 |> Js.Float.toFixedWithPrecision(~digits=2))
    | MB =>
      value
      |> float_of_int
      |> (
        x => x /. 1024.0 /. 1024.0 |> Js.Float.toFixedWithPrecision(~digits=2)
      )
    }
  )
  |> ReasonReact.string;

let guessUnit = value =>
  if (value < 10) {
    B;
  } else if (value < 10 * 1024) {
    KB;
  } else {
    MB;
  };

let displayUnit = unit =>
  (
    switch (unit) {
    | B => "B"
    | KB => "kB"
    | MB => "MB"
    }
  )
  |> ReasonReact.string;

let component = ReasonReact.statelessComponent("Size");

let make = (~value, ~className="", _children) => {
  ...component,
  render: _self => {
    let unit = guessUnit(value);

    <span className>
      {displayValue(value, unit)}
      {ReasonReact.string(" ")}
      {displayUnit(unit)}
    </span>;
  },
};