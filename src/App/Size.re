type sizeUnit =
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
  |> React.string;

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
  |> React.string;

let component = ReasonReact.statelessComponent("Size");

let make = (~className="", ~value) => {
  ...component,
  render: _self => {
    let unit = guessUnit(value);

    <span className>
      {displayValue(value, unit)}
      {React.string(" ")}
      {displayUnit(unit)}
    </span>;
  },
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component,
    (
      reactProps: {
        .
        "className": option('className),
        "value": 'value,
      },
    ) =>
    make(~className=?reactProps##className, ~value=reactProps##value)
  );
[@bs.obj]
external makeProps:
  (~value: 'value, ~className: 'className=?, unit) =>
  {
    .
    "className": option('className),
    "value": 'value,
  } =
  "";