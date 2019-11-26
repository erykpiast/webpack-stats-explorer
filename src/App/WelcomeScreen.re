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

  let paste =
    style([
      fontSize(Theme.Size.Text.default),
      fontFamily(`monospace),
      minHeight(em(5.0)),
      width(`percent(80.0)),
      margin2(~v=px(0), ~h=`auto),
      maxWidth(Theme.Space.quadruplehexteenfold),
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

let loadExampleData = _ => [Data.a, Data.b, Data.c, Data.d, Data.e];

[@react.component]
let make = (~onStats, ~children) => {
  <Dropzone className=Styles.dropzone onStats={Array.to_list ||> onStats}>
    {onClick =>
       children(
         <div className=Styles.wrapper>
           <p> {L10N.Welcome.paste |> React.string} </p>
           <div> <FetchArea className=Styles.paste onStats /> </div>
           <p>
             {L10N.Welcome.or_ ++ " " ++ L10N.Welcome.drag |> React.string}
           </p>
           <div>
             <Button onClick type_=Button.Primary className=Styles.action>
               {L10N.Welcome.upload |> React.string}
             </Button>
           </div>
           <p> {L10N.Welcome.or_ |> React.string} </p>
           <div>
             <Button
               onClick={loadExampleData ||> onStats} className=Styles.action>
               {L10N.Welcome.loadExample |> React.string}
             </Button>
           </div>
         </div>,
       )}
  </Dropzone>;
};