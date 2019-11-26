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

type failReason =
  | NotEnoughFiles
  | WrongFormat
  | ParsingFailed
  | UnsupportedVersion;

type status =
  | Success
  | Fail(failReason)
  | Unknown;

type state = {
  status,
  resetParsingStatusTimeout: option(Js.Global.timeoutId),
};

type action =
  | UploadSuccess(Js.Global.timeoutId)
  | UploadFail(failReason, Js.Global.timeoutId)
  | StatusReset;

exception NotEnoughFilesExn;

let getLabel = status =>
  switch (status) {
  | Success => Some(L10N.Validation.success)
  | Fail(reason) =>
    switch (reason) {
    | NotEnoughFiles => Some(L10N.Validation.notEnough)
    | WrongFormat => Some(L10N.Validation.json)
    | ParsingFailed => Some(L10N.Validation.stats)
    | UnsupportedVersion => Some(L10N.Validation.version)
    }
  | Unknown => None
  };

let reducer = (_state, action) =>
  switch (action) {
  | UploadSuccess(timeoutId) => {
      status: Success,
      resetParsingStatusTimeout: Some(timeoutId),
    }
  | UploadFail(reason, timeoutId) => {
      status: Fail(reason),
      resetParsingStatusTimeout: Some(timeoutId),
    }
  | StatusReset => {status: Unknown, resetParsingStatusTimeout: None}
  };

let fail = (reason, timeoutId) => UploadFail(reason, timeoutId);

let success = timeoutId => UploadSuccess(timeoutId);

[@react.component]
let make = (~onStats, ~children) => {
  let (state, send) =
    React.useReducer(
      reducer,
      {status: Unknown, resetParsingStatusTimeout: None},
    );

  let updateStatus = actionCreator => {
    switch (state.resetParsingStatusTimeout) {
    | Some(timeoutId) => Js.Global.clearTimeout(timeoutId)
    | _ => ()
    };
    let timeoutId = Js.Global.setTimeout(() => send(StatusReset), 5000);

    send(actionCreator(timeoutId));
  };

  let failureHandler =
    [@bs.open]
    (
      fun
      | WebpackStats.FromText.UnsupportedVersionExn => UnsupportedVersion
      | WebpackStats.FromText.ParsingFailedExn => ParsingFailed
      | NotEnoughFilesExn => NotEnoughFiles
    )
    ||> Utils.defaultTo(ParsingFailed)
    ||> (err => updateStatus(fail(err)));

  let onFiles =
    Js.Promise.(
      then_(Array.map(WebpackStats.FromText.make) ||> all)
      ||> then_(files =>
            if (Array.length(files) > 1) {
              updateStatus(success);
              onStats(files |> Array.to_list) |> resolve;
            } else {
              reject(NotEnoughFilesExn);
            }
          )
      ||> catch(failureHandler ||> resolve)
      ||> ignore
    );

  let label = getLabel(state.status);

  <Dropzone className=Styles.dropzone onFiles label>
    {onClick =>
       children(
         <div className=Styles.wrapper>
           <p> {L10N.Welcome.paste |> React.string} </p>
           <div> <FetchArea className=Styles.paste onFiles /> </div>
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
               onClick={loadExampleData ||> onStats ||> ignore}
               className=Styles.action>
               {L10N.Welcome.loadExample |> React.string}
             </Button>
           </div>
         </div>,
       )}
  </Dropzone>;
};