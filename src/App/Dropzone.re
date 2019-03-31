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
) => switch status {
  | Success => Some(L10N.Validation.success)
  | Fail(reason) => switch reason {
    | NotEnoughFiles => Some(L10N.Validation.notEnough)
    | WrongFormat => Some(L10N.Validation.json)
    | ParsingFailed => Some(L10N.Validation.stats)
    }
  | Unknown => if (!isDragActive) {
      None
    } else if (isDragAccept) {
      Some(L10N.drop)
    } else if (isDragReject) {
      Some(L10N.Validation.json)
    } else {
      None
    }
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

  let input = style([
  ]);

  let label = style([
    display(`flex),
    justifyContent(`center),
    alignItems(`center),
    position(`absolute),
    bottom(px(0)),
    left(px(0)),
    right(px(0)),
    top(px(0)),
    zIndex(1),
    backgroundColor(rgba(255, 255, 255, 0.5)),
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

let make = (~onStats, children) => {
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
      }, 2000);

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
          onBlur=rootProps.onBlur
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
          ...(Array.append([|
            <div className=Styles.input>
              <label onClick=rootProps.onClick>
                {L10N.upload |> ReasonReact.string}
              </label>
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
            </div>,
            switch (label) {
            | Some(label) => (<span className=Styles.label>
                {label |> ReasonReact.string}
              </span>)
            | None => ReasonReact.null
            }
          |], children))
        </div>
      })</ReactDropzone>
    </>
  }
};
