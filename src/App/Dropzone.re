type failReason =
  | NotEnoughFiles
  | WrongFormat
  | ParsingFailed;

type status =
  | Success
  | Fail(failReason)
  | Unknown;

type state = {
  status: status,
  resetParsingStatusTimeout: option(Js.Global.timeoutId)
};

type action =
  | UploadSuccess(Js.Global.timeoutId)
  | UploadFail(failReason, Js.Global.timeoutId)
  | StatusReset;

let getLabel = (
  ~isDragAccept,
  ~isDragActive,
  ~isDragReject,
  ~status
) => {
  switch status {
  | Success => "Webpack stats uploaded successfully!"
  | Fail(reason) =>
    switch reason {
    | NotEnoughFiles => "Dude, there is no point in comparing less than two files."
    | WrongFormat => "Drag JSON files, please!"
    | ParsingFailed => "It doesn't seem to be valid Webpack stats."
    }
  | Unknown => if (!isDragActive) {
      "Drop files here"
    } else if (isDragAccept) {
      "Great, drop it now!"
    } else if (isDragReject) {
      "Nope, we need JSON here."
    } else {
      "Here, here!"
    }
  };
};

let parseStats = (~onSuccess, ~onFailure, files) =>
  files
  |> Array.map((file) => file
    |> FileReader.File.asBlob
    |> (blob) => FileReader.toText(blob, ())
    |> Js.Promise.then_((text) => text
      |> Json.parseOrRaise
      |> Stats.decode
      |> Js.Promise.resolve
    )
  )
  |> Js.Promise.all
  |> Js.Promise.then_((files) => {
    if (Array.length(files) > 0) {
      onSuccess(files);
    }

    Js.Promise.resolve();
  })
  |> Js.Promise.catch((err) => {
    Js.log(err);
    onFailure(err);
    Js.Promise.resolve();
  });

module Styles = {
  open Css;

  let dropzone = style([
    display(`flex),
    justifyContent(`center),
    alignItems(`center),
    position(`absolute),
    height(`percent(100.0)),
    width(`percent(100.0)),
    zIndex(-1),
  ]);
};

let reducer = (action, _state) =>
  switch action {
  | UploadSuccess(timeoutId) => ReasonReact.Update({
      status: Success,
      resetParsingStatusTimeout: Some(timeoutId)
    })
  | UploadFail(reason, timeoutId) => ReasonReact.Update({
      status: Fail(reason),
      resetParsingStatusTimeout: Some(timeoutId)
    })
  | StatusReset => ReasonReact.Update({
      status: Unknown,
      resetParsingStatusTimeout: None
    })
};

let fail = (reason, timeoutId) => UploadFail(reason, timeoutId);

let success = (timeoutId) => UploadSuccess(timeoutId);

let component = ReasonReact.reducerComponent("Dropzone");

let make = (~onStats, _children) => {
  ...component,
  initialState: () => {
    status: Unknown,
    resetParsingStatusTimeout: None,
  },
  reducer,
  render: self => {
    let updateStatus = (actionCreator) => {
      switch self.state.resetParsingStatusTimeout {
        | Some(timeoutId) => Js.Global.clearTimeout(timeoutId)
        | _ => ()
        };
      let timeoutId = Js.Global.setTimeout(() => {
        self.send(StatusReset);
      }, 1000);

      self.send(actionCreator(timeoutId));
    };

    <>
      <ReactDropzone
        accept=ReactDropzone.Single("application/json")
        multiple=true
        onDrop=((acceptedFiles, _) => switch acceptedFiles {
        | [||] => updateStatus(fail(NotEnoughFiles))
        | [|_|] => updateStatus(fail(NotEnoughFiles))
        | files => files |> parseStats(
            ~onSuccess = (stats) => {
              updateStatus(success)
              onStats(stats);
            },
            ~onFailure = (_) => {
              updateStatus(fail(ParsingFailed))
            },
          ) |> ignore
        })
      >
      ...(({ getInputProps, getRootProps, isDragAccept, isDragActive, isDragReject, rejectedFiles, acceptedFiles }) => {
        let inputProps = getInputProps();
        let rootProps = getRootProps();
        let label = getLabel(
          ~isDragAccept,
          ~isDragActive,
          ~isDragReject,
          ~status = self.state.status,
        );
        <div
          className=Styles.dropzone
          onBlur=rootProps.onBlur
          onClick=rootProps.onClick
          onDragEnter=rootProps.onDragEnter
          onDragLeave=rootProps.onDragLeave
          onDragOver=rootProps.onDragOver
          onDragStart=rootProps.onDragStart
          onDrop=rootProps.onDrop
          onFocus=rootProps.onFocus
          onKeyDown=rootProps.onKeyDown
          ref=rootProps.ref
          tabIndex=rootProps.tabIndex
        >
          <span>
            <label>{ReasonReact.string(label)}</label>
            <input
              autoComplete=inputProps.autoComplete
              onChange=inputProps.onChange
              onClick=inputProps.onClick
              ref=inputProps.ref
              style=inputProps.style
              tabIndex=inputProps.tabIndex
              type_=inputProps.type_
              multiple=inputProps.multiple
            />
          </span>
        </div>
      })</ReactDropzone>
    </>
  }
};
