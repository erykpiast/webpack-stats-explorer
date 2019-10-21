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
  render: _self =>
    <div className=Styles.wrapper>
      <Button onClick=onPrev> (triangle |> React.string) </Button>
      <span className=Styles.value>
        (currentIndex + 1 |> string_of_int |> React.string)
        ("/" |> React.string)
        (comparisons |> List.length |> string_of_int |> React.string)
      </span>
      <Button onClick=onNext>
        <span className=Styles.nextButtonLabel>
          (triangle |> React.string)
        </span>
      </Button>
    </div>,
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
        "currentIndex": 'currentIndex,
        "onPrev": 'onPrev,
        "onNext": 'onNext,
        "comparisons": 'comparisons,
        "children": 'children,
      },
    ) =>
    make(
      ~currentIndex=reactProps##currentIndex,
      ~onPrev=reactProps##onPrev,
      ~onNext=reactProps##onNext,
      ~comparisons=reactProps##comparisons,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~comparisons: 'comparisons,
    ~onNext: 'onNext,
    ~onPrev: 'onPrev,
    ~currentIndex: 'currentIndex,
    unit
  ) =>
  {
    .
    "currentIndex": 'currentIndex,
    "onPrev": 'onPrev,
    "onNext": 'onNext,
    "comparisons": 'comparisons,
    "children": 'children,
  } =
  "";
