open Rationale.Function.Infix;

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

let getLabel = (~isDragAccept, ~isDragActive, ~isDragReject, ~status) =>
  switch (status) {
  | Success => Some(L10N.Validation.success)
  | Fail(reason) =>
    switch (reason) {
    | NotEnoughFiles => Some(L10N.Validation.notEnough)
    | WrongFormat => Some(L10N.Validation.json)
    | ParsingFailed => Some(L10N.Validation.stats)
    | UnsupportedVersion => Some(L10N.Validation.version)
    }
  | Unknown =>
    if (!isDragActive) {
      None;
    } else if (isDragAccept) {
      Some(L10N.drop);
    } else if (isDragReject) {
      Some(L10N.Validation.json);
    } else {
      None;
    }
  };

let parseStats =
  Js.Promise.(
    Array.map(
      FileReader.File.asBlob
      ||> (
        blob =>
          FileReader.toText2(blob, ~encoding="UTF-8")
          |> then_(WebpackStats.FromText.make)
      ),
    )
    ||> all
    ||> then_(files =>
          if (Array.length(files) > 0) {
            resolve(files);
          } else {
            reject(NotEnoughFilesExn);
          }
        )
  );

module Styles = {
  open Css;

  let input = style([]);

  let label = style([backgroundColor(Theme.Color.Background.danger)]);
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
let make = (~onStats, ~className="", ~children) => {
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

  <ReactDropzone
    accept={ReactDropzone.Single("application/json")}
    multiple=true
    onDrop={(acceptedFiles, _) =>
      switch (acceptedFiles) {
      | [||] => updateStatus(fail(NotEnoughFiles))
      | [|_|] => updateStatus(fail(NotEnoughFiles))
      | files =>
        Js.Promise.(
          files
          |> parseStats
          |> then_(stats => {
               updateStatus(success);
               onStats(stats) |> ignore |> resolve;
             })
          |> catch(failureHandler ||> resolve)
          |> ignore
        )
      }
    }>
    {(
       {getInputProps, getRootProps, isDragAccept, isDragActive, isDragReject},
     ) => {
       let inputProps = getInputProps();
       let rootProps = getRootProps();
       let label =
         getLabel(
           ~isDragAccept,
           ~isDragActive,
           ~isDragReject,
           ~status=state.status,
         );
       <div
         className
         onBlur={rootProps.onBlur}
         onDragEnter={rootProps.onDragEnter}
         onDragLeave={rootProps.onDragLeave}
         onDragOver={rootProps.onDragOver}
         onDragStart={rootProps.onDragStart}
         onDrop={rootProps.onDrop}
         onFocus={rootProps.onFocus}
         onKeyDown={rootProps.onKeyDown}
         ref={ReactDOMRe.Ref.callbackDomRef(rootProps.ref)}
         tabIndex={rootProps.tabIndex}>
         <div className=Styles.input>
           <input
             autoComplete={inputProps.autoComplete}
             onChange={inputProps.onChange}
             onClick={inputProps.onClick}
             ref={ReactDOMRe.Ref.callbackDomRef(inputProps.ref)}
             style={inputProps.style}
             tabIndex={inputProps.tabIndex}
             type_={inputProps.type_}
             multiple={inputProps.multiple}
           />
         </div>
         {switch (label) {
          | Some(label) =>
            <Snackbar className=Styles.label>
              {label |> React.string}
            </Snackbar>
          | None => React.null
          }}
         {children(rootProps.onClick)}
       </div>;
     }}
  </ReactDropzone>;
};