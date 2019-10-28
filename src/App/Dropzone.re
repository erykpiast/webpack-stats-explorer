type failReason =
  | NotEnoughFiles
  | WrongFormat
  | ParsingFailed
  | UnsupportedVersion;

exception UnsupportedVersionExn;
exception ParsingFailedExn;

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

let parseStats = (~onSuccess, ~onFailure, files) =>
  files
  |> Array.map(file =>
       file
       |> FileReader.File.asBlob
       |> (
         blob =>
           FileReader.toText2(blob, ~encoding="UTF-8")
           |> Js.Promise.then_(text => {
                let version =
                  text
                  |> Json.parseOrRaise
                  |> WebpackStats.Version.decode
                  |> WebpackStats.Version.isSupported;

                if (version) {
                  try (
                    text
                    |> Json.parseOrRaise
                    |> WebpackStats.decode
                    |> Js.Promise.resolve
                  ) {
                  | err =>
                    Js.log(err);
                    Js.Promise.reject(ParsingFailedExn);
                  };
                } else {
                  Js.Promise.reject(UnsupportedVersionExn);
                };
              })
       )
     )
  |> Js.Promise.all
  |> Js.Promise.then_(files => {
       if (Array.length(files) > 0) {
         onSuccess(files);
       };

       Js.Promise.resolve();
     })
  |> Js.Promise.catch(err => {
       Js.log(err);
       onFailure(err);
       Js.Promise.resolve();
     });

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
    Rationale.Function.Infix.(
      [@bs.open]
      (
        fun
        | UnsupportedVersionExn => UnsupportedVersion
        | ParsingFailedExn => ParsingFailed
      )
      ||> Utils.defaultTo(ParsingFailed)
      ||> (err => updateStatus(fail(err)))
    );

  <ReactDropzone
    accept={ReactDropzone.Single("application/json")}
    multiple=true
    onDrop={(acceptedFiles, _) =>
      switch (acceptedFiles) {
      | [||] => updateStatus(fail(NotEnoughFiles))
      | [|_|] => updateStatus(fail(NotEnoughFiles))
      | files =>
        files
        |> parseStats(
             ~onSuccess=
               stats => {
                 updateStatus(success);
                 onStats(stats);
               },
             ~onFailure=failureHandler,
           )
        |> ignore
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