open Rationale.Function.Infix;

let component = ReasonReact.statelessComponent("WelcomeScreen");

module Styles = {
  open Css;

  let dropzone = style([height(`percent(100.0))]);

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
      width(`percent(100.0)),
      justifyContent(`center),
      textAlign(`center),
    ]);

  let action =
    style([
      fontSize(em(1.5)),
      padding2(~v=Theme.Space.double, ~h=Theme.Space.quadruple),
    ]);
};

let logStats = (title, stats) => {
  Js.log(title);
  stats |> WebpackStats.encode |> Js.log;
};

let logComp = (title, comp) => {
  Js.log(title);
  comp |> CompareEntry.encode |> Js.log;
};

let compareStats = Array.to_list ||> CompareStats.make;

let loadExampleData = () =>
  compareStats([|Data.a, Data.b, Data.c, Data.d, Data.e|]);

let make = (~onStats, children) => {
  ...component,
  render: _self =>
    <Dropzone className=Styles.dropzone onStats=(compareStats ||> onStats)>
      ...(
           onClick => [|
             children(
               <div className=Styles.wrapper>
                 <p> (L10N.drag |> React.string) </p>
                 <div>
                   <Button
                     onClick type_=Button.Primary className=Styles.action>
                     (L10N.upload |> React.string)
                   </Button>
                 </div>
                 <p> (L10N.or_ |> React.string) </p>
                 <div>
                   <Button
                     onClick=(_ => onStats(loadExampleData()))
                     className=Styles.action>
                     (L10N.loadExample |> React.string)
                   </Button>
                 </div>
               </div>,
             ),
           |]
         )
    </Dropzone>,
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
        "onStats": 'onStats,
        "children": 'children,
      },
    ) =>
    make(~onStats=reactProps##onStats, reactProps##children)
  );
[@bs.obj]
external makeProps:
  (~children: 'children, ~onStats: 'onStats, unit) =>
  {
    .
    "onStats": 'onStats,
    "children": 'children,
  } =
  "";
