let component = ReasonReact.statelessComponent("ComparisonChooser");

module Styles = {
  open Css;

  let wrapper =
    style([
      display(`flex),
      alignItems(`center),
      color(Theme.Color.Text.primary),
    ]);

  let nextButtonLabel =
    style([display(`inlineBlock), transform(rotate(deg(180.0)))]);

  let value = style([margin(Theme.Space.double)]);
};

let triangle = {js|◁|js};

let make = (~comparisons, ~onNext, ~onPrev, ~currentIndex, _children) => {
  ...component,
  render: _self => {
    <div className=Styles.wrapper>
      <Button onClick=onPrev> {triangle |> ReasonReact.string} </Button>
      <span className=Styles.value>
        {currentIndex + 1 |> string_of_int |> ReasonReact.string}
        {"/" |> ReasonReact.string}
        {comparisons |> List.length |> string_of_int |> ReasonReact.string}
      </span>
      <Button onClick=onNext>
        <span className=Styles.nextButtonLabel>
          {triangle |> ReasonReact.string}
        </span>
      </Button>
    </div>;
  },
};