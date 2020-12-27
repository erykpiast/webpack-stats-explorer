open Rationale.Function.Infix;

module Styles = {
  open Css;

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

let loadExampleData = _ => [Data.a, Data.b, Data.c, Data.d];

[@react.component]
let make = (~urls, ~onStats, ~onUrls, ~onExample, ~children) => {
  <AddStats onStats>
    {(triggerUpload, onFiles) =>
       children(
         <div className=Styles.wrapper>
           <p> {L10N.Welcome.paste |> React.string} </p>
           <div>
             <FetchArea className=Styles.paste urls onFiles onUrls />
           </div>
           <p>
             {L10N.Welcome.or_ ++ " " ++ L10N.Welcome.drag |> React.string}
           </p>
           <div>
             <Button
               onClick=triggerUpload
               type_=Button.Primary
               className=Styles.action
               id="load-custom">
               {L10N.Welcome.upload |> React.string}
             </Button>
           </div>
           <p> {L10N.Welcome.or_ |> React.string} </p>
           <div>
             <Button
               onClick={loadExampleData ||> onStats ||> ignore ||> onExample}
               className=Styles.action
               id="load-example">
               {L10N.Welcome.loadExample |> React.string}
             </Button>
           </div>
         </div>,
       )}
  </AddStats>;
};