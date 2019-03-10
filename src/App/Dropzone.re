open Rationale.Function.Infix;

[@bs.module "react-dropzone"] external reactClass: ReasonReact.reactClass = "default";

type accept =
  | Single(string)
  | Multi(array(string));

[@bs.deriving abstract]
type file = {
  lastModified: int,
  name: string,
  size: int,
  [@bs.as "type"] type_: string,
};

type onClick = ReactEvent.Mouse.t => unit;
type onKeyDown = ReactEvent.Keyboard.t => unit;
type onFocus = ReactEvent.Focus.t => unit;
type onBlur = ReactEvent.Focus.t => unit;
type onDragStart = ReactEvent.Mouse.t => unit;
type onDragEnter = ReactEvent.Mouse.t => unit;
type onDragOver = ReactEvent.Mouse.t => unit;
type onDragLeave = ReactEvent.Mouse.t => unit;
type ref = Js.nullable(Dom.element) => unit;

[@bs.deriving abstract]
type props = {
  [@bs.optional] accept: accept,
  [@bs.optional] disabled: bool,
  [@bs.optional] maxSize: int,
  [@bs.optional] minSize: int,
  [@bs.optional] multiple: bool,
  [@bs.optional] name: string,
  [@bs.optional] onBlur: onBlur,
  [@bs.optional] onClick: onClick,
  [@bs.optional] onDragEnter: onDragEnter,
  [@bs.optional] onDragLeave: onDragLeave,
  [@bs.optional] onDragOver: onDragOver,
  [@bs.optional] onDragStart: onDragStart,
  [@bs.optional] onDrop: (array(file), array(file)) => unit,
  [@bs.optional] onDropAccepted: ReactEvent.Mouse.t => unit,
  [@bs.optional] onDropRejected: ReactEvent.Mouse.t => unit,
  [@bs.optional] onFileDialogCancel: ReactEvent.Mouse.t => unit,
  [@bs.optional] onFocus: onFocus,
  [@bs.optional] onKeyDown: onKeyDown,
  [@bs.optional] preventDropOnDocument: bool,
};

module GetInputProps = {
  type onChange = ReactEvent.Form.t => unit;

  module Input = {
    [@bs.deriving abstract]
    type js = {
      [@bs.optional] refKey: string,
      [@bs.optional] onChange: onChange,
      [@bs.optional] onClick: onClick,
    };

    type t = {
      refKey: option(string),
      onChange: option(onChange),
      onClick: option(onClick),
    };
  };

  module Output = {
    [@bs.deriving abstract]
    type js = {
      [@bs.as "type"] type_: string,
      autoComplete: string,
      onChange: onChange,
      onClick: onClick,
      tabIndex: int,
      style: ReactDOMRe.style,
      ref: ref,
    };

    type t = {
      type_: string,
      autoComplete: string,
      onChange: onChange,
      onClick: onClick,
      tabIndex: int,
      style: ReactDOMRe.style,
      ref: ref,
    };

    let make = (js) => {
      type_: js->type_Get,
      autoComplete: js->autoCompleteGet,
      onChange: js->onChangeGet,
      onClick: js->onClickGet,
      tabIndex: js->tabIndexGet,
      style: js->styleGet,
      ref: js->refGet,
    };
  };

  type js = Input.js => Output.js;
  type t = (
    ~refKey: string=?,
    ~onChange: onChange=?,
    ~onClick: onClick=?,
    unit
  ) => Output.t;

  let make = (fn) => (
    ~refKey=?,
    ~onChange=?,
    ~onClick=?,
    ()
  ) => Input.js(
    ~refKey=?refKey,
    ~onChange=?onChange,
    ~onClick=?onClick,
    ()
  ) |> fn |> Output.make;
};

module GetRootProps = {
  type onDrop = ReactEvent.Mouse.t => unit;

  module Input = {
    [@bs.deriving abstract]
    type js = {
      [@bs.optional] refKey: string,
      [@bs.optional] onKeyDown: onKeyDown,
      [@bs.optional] onFocus: onFocus,
      [@bs.optional] onBlur: onBlur,
      [@bs.optional] onClick: onClick,
      [@bs.optional] onDragStart: onDragStart,
      [@bs.optional] onDragEnter: onDragEnter,
      [@bs.optional] onDragOver: onDragOver,
      [@bs.optional] onDragLeave: onDragLeave,
      [@bs.optional] onDrop: onDrop,
    };

    type t = {
      refKey: option(string),
      onKeyDown: option(onKeyDown),
      onFocus: option(onFocus),
      onBlur: option(onBlur),
      onClick: option(onClick),
      onDragStart: option(onDragStart),
      onDragEnter: option(onDragEnter),
      onDragOver: option(onDragOver),
      onDragLeave: option(onDragLeave),
      onDrop: option(onDrop),
    };
  };

  module Output = {
    [@bs.deriving abstract]
    type js = {
      onKeyDown: onKeyDown,
      onFocus: onFocus,
      onBlur: onBlur,
      onClick: onClick,
      onDragStart: onDragStart,
      onDragEnter: onDragEnter,
      onDragOver: onDragOver,
      onDragLeave: onDragLeave,
      onDrop: onDrop,
      tabIndex: int,
      ref: ref
    };

    type t = {
      onKeyDown: onKeyDown,
      onFocus: onFocus,
      onBlur: onBlur,
      onClick: onClick,
      onDragStart: onDragStart,
      onDragEnter: onDragEnter,
      onDragOver: onDragOver,
      onDragLeave: onDragLeave,
      onDrop: onDrop,
      tabIndex: int,
      ref: ref
    };

    let make = (js) => {
      onKeyDown: js->onKeyDownGet,
      onFocus: js->onFocusGet,
      onBlur: js->onBlurGet,
      onClick: js->onClickGet,
      onDragStart: js->onDragStartGet,
      onDragEnter: js->onDragEnterGet,
      onDragOver: js->onDragOverGet,
      onDragLeave: js->onDragLeaveGet,
      onDrop: js->onDropGet,
      tabIndex: js->tabIndexGet,
      ref: js->refGet,
    };
  }

  type js = Input.js => Output.js;
  type t = (
    ~refKey: string=?,
    ~onKeyDown: onKeyDown=?,
    ~onFocus: onFocus=?,
    ~onBlur: onBlur=?,
    ~onClick: onClick=?,
    ~onDragStart: onDragStart=?,
    ~onDragEnter: onDragEnter=?,
    ~onDragOver: onDragOver=?,
    ~onDragLeave: onDragLeave=?,
    ~onDrop: onDrop=?,
    unit
  ) => Output.t;

  let make = (fn) => (
    ~refKey=?,
    ~onKeyDown=?,
    ~onFocus=?,
    ~onBlur=?,
    ~onClick=?,
    ~onDragStart=?,
    ~onDragEnter=?,
    ~onDragOver=?,
    ~onDragLeave=?,
    ~onDrop=?,
    ()
  ) => Input.js(
    ~refKey=?refKey,
    ~onKeyDown=?onKeyDown,
    ~onFocus=?onFocus,
    ~onBlur=?onBlur,
    ~onClick=?onClick,
    ~onDragStart=?onDragStart,
    ~onDragEnter=?onDragEnter,
    ~onDragOver=?onDragOver,
    ~onDragLeave=?onDragLeave,
    ~onDrop=?onDrop,
    ()
  ) |> fn |> Output.make;
};

module Children = {
  module Input = {
    [@bs.deriving abstract]
    type js = {
      getRootProps: GetRootProps.js,
      getInputProps: GetInputProps.js,
      [@bs.as "open"] open_: unit => unit,
      isDragActive: bool,
      isDragAccept: bool,
      isDragReject: bool,
      isFocused: bool,
      acceptedFiles: array(file),
      rejectedFiles: array(file),
      draggedFiles: array(file)
    };

    type t = {
      getRootProps: GetRootProps.t,
      getInputProps: GetInputProps.t,
      open_: unit => unit,
      isDragActive: bool,
      isDragAccept: bool,
      isDragReject: bool,
      isFocused: bool,
      acceptedFiles: array(file),
      rejectedFiles: array(file),
      draggedFiles: array(file),
    };

    let make = (js) => {
      getRootProps: js->getRootPropsGet |> Utils.Function.unary |> GetRootProps.make,
      getInputProps: js->getInputPropsGet |> Utils.Function.unary |> GetInputProps.make,
      open_: js->open_Get,
      isDragActive: js->isDragActiveGet,
      isDragAccept: js->isDragAcceptGet,
      isDragReject: js->isDragRejectGet,
      isFocused: js->isFocusedGet,
      acceptedFiles: js->acceptedFilesGet,
      rejectedFiles: js->rejectedFilesGet,
      draggedFiles: js->draggedFilesGet,
    };
  };

  type t = Input.t => ReasonReact.reactElement;

  let make = (||>)(Input.make);
}

let make = (
  ~accept=?,
  ~disabled=?,
  ~maxSize=?,
  ~minSize=?,
  ~multiple=?,
  ~name=?,
  ~onBlur=?,
  ~onClick=?,
  ~onDragEnter=?,
  ~onDragLeave=?,
  ~onDragOver=?,
  ~onDragStart=?,
  ~onDrop=?,
  ~onDropAccepted=?,
  ~onDropRejected=?,
  ~onFileDialogCancel=?,
  ~onFocus=?,
  ~onKeyDown=?,
  ~preventDropOnDocument=?,
  children: Children.t
) => ReasonReact.wrapJsForReason(
  ~reactClass,
  ~props=props(
    ~accept=?accept,
    ~disabled=?disabled,
    ~maxSize=?maxSize,
    ~minSize=?minSize,
    ~multiple=?multiple,
    ~name=?name,
    ~onBlur=?onBlur,
    ~onClick=?onClick,
    ~onDragEnter=?onDragEnter,
    ~onDragLeave=?onDragLeave,
    ~onDragOver=?onDragOver,
    ~onDragStart=?onDragStart,
    ~onDrop=?onDrop,
    ~onDropAccepted=?onDropAccepted,
    ~onDropRejected=?onDropRejected,
    ~onFileDialogCancel=?onFileDialogCancel,
    ~onFocus=?onFocus,
    ~onKeyDown=?onKeyDown,
    ~preventDropOnDocument=?preventDropOnDocument,
    ()
  ),
  Children.make(children)
);
