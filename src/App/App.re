type activeChunk =
  | Some(Compare.Chunks.chunk)
  | None;

type state = {
  index: int,
  comparisons: list(Compare.t),
  activeChunk: activeChunk
};

type action =
  | Next
  | Prev
  | ChooseChunk(Compare.Chunks.chunk);

let component = ReasonReact.reducerComponent("App");
let reducer = (action, state) =>
  switch (action) {
  | Next => ReasonReact.Update({
      index: (state.index + 1) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      activeChunk: None
    })
  | Prev => ReasonReact.Update({
      index: (state.index - 1 + List.length(state.comparisons)) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      activeChunk: None
    })
  | ChooseChunk(chunk) => ReasonReact.Update({
    index: state.index,
    comparisons: state.comparisons,
    activeChunk: Some(chunk)
  })
};

module Styles = {
  open Css;

  let wrapper = style([
    display(`flex),
    width(`percent(100.0)),
  ]);

  let column = style([
    display(block),
    width(`percent(50.0)),
  ]);

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

let getLabel = (~isDragAccept, ~isDragActive, ~isDragReject) => {
  if (!isDragActive) {
    "Drop files here"
  } else if (isDragAccept) {
    "Great, drop it now!"
  } else if (isDragReject) {
    "Nope, we need JSON here."
  } else {
    "Here, here!"
  }
};

let make = (~comparisons, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => {
    index: 0,
    comparisons: comparisons,
    activeChunk: None
  },

  /* State transitions */
  reducer,

  render: self => {
    let comp = List.nth(self.state.comparisons, self.state.index);

    <>
      <Dropzone
        accept=Dropzone.Single("application/json")
        multiple=true
        onDrop=((a, b) => Js.log((a, b)))
      >
      ...(({ getInputProps, getRootProps, isDragAccept, isDragActive, isDragReject }) => {
        let inputProps = getInputProps();
        let rootProps = getRootProps();
        let label = getLabel(~isDragAccept, ~isDragActive, ~isDragReject);
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
            />
          </span>
        </div>
      })</Dropzone>
      <button onClick=(_ => self.send(Prev))>
        {ReasonReact.string("<<")}
      </button>
      {self.state.index + 1 |> string_of_int |> ReasonReact.string}
      {ReasonReact.string(" of ")}
      {self.state.comparisons |> List.length |> string_of_int |> ReasonReact.string}
      <button onClick=(_ => self.send(Next))>
        {ReasonReact.string(">>")}
      </button>
      <div className=Styles.wrapper>
        <div className=Styles.column>
          <ChunksCompare
            size=comp.size
            chunks=comp.chunks
            onChunk=((chunk) => self.send(ChooseChunk(chunk)))
          />
        </div>
        <div className=Styles.column>
          {switch self.state.activeChunk {
          | None => ReasonReact.null
          | Some(chunk) => Compare.Modules.(<ModulesCompare
            modules={switch chunk {
            | Summary(chunk) => NotModifiedModules(chunk.modules)
            | ModifiedSummary(chunk) => ModifiedModules(chunk.modules)
            }}
            onModule={(_) => ()}
            title={L10N.modules}
          />)}}
        </div>
      </div>
    </>
  }
};
