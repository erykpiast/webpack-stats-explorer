type parsingStatus =
  | Success
  | Fail
  | Unknown;

type state = {
  parsingStatus: parsingStatus,
  resetParsingStatusTimeout: option(Js.Global.timeoutId)
};

type action =
  | ParsingSucceed(Js.Global.timeoutId)
  | ParsingFailed(Js.Global.timeoutId)
  | ParsingReset;

let getLabel = (
  ~isDragAccept,
  ~isDragActive,
  ~isDragReject,
  ~parsingStatus
) => {
  switch parsingStatus {
  | Success => "Webpack stats parsed successfully!"
  | Fail    => "Parsing failed miserably!"
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
    onSuccess(files);
    Js.Promise.resolve();
  })
  |> Js.Promise.catch((err) => {
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

let reducer = (action, state) =>
  switch action {
  | ParsingSucceed(timeoutId) => ReasonReact.Update({
      parsingStatus: Success,
      resetParsingStatusTimeout: Some(timeoutId)
    })
  | ParsingFailed(timeoutId) => ReasonReact.Update({
      parsingStatus: Fail,
      resetParsingStatusTimeout: Some(timeoutId)
    })
  | ParsingReset => ReasonReact.Update({
      parsingStatus: Unknown,
      resetParsingStatusTimeout: None
    })
};

let component = ReasonReact.reducerComponent("Dropzone");

let resetTimeout = (previousTimeout, send) => {
  switch previousTimeout {
  | Some(timeoutId) => Js.Global.clearTimeout(timeoutId)
  | _ => ()
  };
  Js.Global.setTimeout(() => send(ParsingReset), 1000)
};

let make = (~onStats, _children) => {
  ...component,
  initialState: () => {
    parsingStatus: Unknown,
    resetParsingStatusTimeout: None,
  },
  reducer,
  render: self => {
    <>
      <ReactDropzone
        accept=ReactDropzone.Single("application/json")
        multiple=true
        onDrop=((acceptedFiles, _) => acceptedFiles
          |> parseStats(
            ~onSuccess = (stats) => {
              let timeout = resetTimeout(
                self.state.resetParsingStatusTimeout,
                self.send
              );
              self.send(ParsingSucceed(timeout));
              onStats(stats);
            },
            ~onFailure = (_) => {
              let timeout = resetTimeout(
                self.state.resetParsingStatusTimeout,
                self.send
              );
              self.send(ParsingFailed(timeout));
            },
          )
          |> ignore
        )
      >
      ...(({ getInputProps, getRootProps, isDragAccept, isDragActive, isDragReject }) => {
        let inputProps = getInputProps();
        let rootProps = getRootProps();
        let label = getLabel(
          ~isDragAccept,
          ~isDragActive,
          ~isDragReject,
          ~parsingStatus = self.state.parsingStatus,
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
