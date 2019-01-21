type unit = B | KB | MB;

module Styles = {
  open Css;

  let better = style([
    display(inlineBlock),
    backgroundColor(Theme.betterColor),
    padding(Theme.padding),
    before([
      contentRule("-")
    ])
  ]);

  let worse = style([
    display(inlineBlock),
    backgroundColor(Theme.worseColor),
    padding(Theme.padding),
    before([
      contentRule("+")
    ])
  ]);
};

let displayValue = (value, unit) =>
  switch (unit) {
  | B => value |> string_of_int
  | KB => value
    |> float_of_int
    |> (x) => (x /. 1024.0)
    |> Js.Float.toFixedWithPrecision(~digits=2)
  | MB => value
    |> float_of_int
    |> (x) => ((x /. 1024.0) /. 1024.0)
    |> Js.Float.toFixedWithPrecision(~digits=2)
  } |> ReasonReact.string

let displayUnit = (unit) => switch (unit) {
  | B => "B"
  | KB => "kB"
  | MB => "MB"
  } |> ReasonReact.string

let component = ReasonReact.statelessComponent("NumericDiff");

let make = (
  _children,
  ~after,
  ~before,
  ~label,
  ~unit,
) => {
  ...component,
  render: _self => {
    let diff = after - before;
    let className = if (diff > 0) Styles.worse else Styles.better;

    <div>
      {ReasonReact.string(label)}
      {ReasonReact.string(": ")}
      {displayValue(after, unit)}
      {ReasonReact.string(" ")}
      {displayUnit(unit)}
      {ReasonReact.string(" ")}
      {diff != 0 ? (
        <span className=className>
          {displayValue(Js.Math.abs_int(diff), unit)}
          {ReasonReact.string(" ")}
          {displayUnit(unit)}
        </span>
      ) : ReasonReact.null}
    </div>;
  },
};
