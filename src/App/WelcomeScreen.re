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
  render: _self => {
    <Dropzone className=Styles.dropzone onStats={compareStats ||> onStats}>
      ...{onClick =>
        [|
          children(
            <div className=Styles.wrapper>
              <p> {L10N.drag |> ReasonReact.string} </p>
              <div>
                <Button onClick type_=Button.Primary className=Styles.action>
                  {L10N.upload |> ReasonReact.string}
                </Button>
              </div>
              <p> {L10N.or_ |> ReasonReact.string} </p>
              <div>
                <Button
                  onClick={_ => onStats(loadExampleData())}
                  className=Styles.action>
                  {L10N.loadExample |> ReasonReact.string}
                </Button>
              </div>
            </div>,
          ),
        |]
      }
    </Dropzone>;
  },
};