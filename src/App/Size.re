type sizeUnit =
  | B
  | KB
  | MB;

let displayValue = (unit, value) =>
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
  |> React.string;

let guessUnit = value =>
  if (value < 10) {
    B;
  } else if (value < 500 * 1024) {
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
  );

[@react.component]
let make = (~className="", ~value) => {
  let unit = guessUnit(value);

  <span className>
    {displayValue(unit, value)}
    {React.string(" ")}
    {displayUnit(unit) |> React.string}
  </span>;
};