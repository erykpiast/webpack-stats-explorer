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

[@react.component]
let make =
    (~comparisons: list(CompareEntry.t), ~onNext, ~onPrev, ~currentIndex) => {
  <div className=Styles.wrapper id="comparison-chooser">
    <Button onClick=onPrev id="prev-comparison"> {triangle |> React.string} </Button>
    <span className=Styles.value>
      {currentIndex + 1 |> string_of_int |> React.string}
      {"/" |> React.string}
      {comparisons |> List.length |> string_of_int |> React.string}
    </span>
    <Button onClick=onNext id="next-comparison">
      <span className=Styles.nextButtonLabel>
        {triangle |> React.string}
      </span>
    </Button>
  </div>;
};