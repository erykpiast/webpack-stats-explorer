open Rationale.Function.Infix;

module Styles = {
  open Css;

  let label = style([backgroundColor(Theme.Color.Background.danger)]);

  let fadeIn = keyframes([(0, [opacity(0.0)]), (100, [opacity(0.5)])]);

  let dragActive =
    style([
      position(`relative),
      before([
        contentRule(`text("")),
        position(`absolute),
        top(Theme.Space.double),
        right(Theme.Space.double),
        bottom(Theme.Space.double),
        left(Theme.Space.double),
        backgroundColor(Theme.Color.Background.bright),
        border(Theme.Space.default, `dashed, Theme.Color.Border.accent),
        animation(
          ~duration=250,
          ~timingFunction=`easeInOut,
          ~fillMode=`forwards,
          fadeIn,
        ),
        zIndex(1),
        boxShadow(
          Shadow.box(
            ~x=px(0),
            ~y=px(0),
            ~blur=px(0),
            ~spread=Theme.Space.double,
            Theme.Color.Background.bright,
          ),
        ),
      ]),
    ]);
};

[@react.component]
let make = (~onFiles, ~label, ~className="", ~children) => {
  <ReactDropzone
    accept={`single("application/json")}
    multiple=true
    onDrop=Js.Promise.(
      (acceptedFiles, _) =>
        acceptedFiles
        |> Array.map(
             FileReader.File.asBlob
             ||> (blob => FileReader.toText2(blob, ~encoding="UTF-8")),
           )
        |> all
        |> onFiles
    )>
    {({getInputProps, getRootProps, isDragActive}) => {
       let inputProps = getInputProps();
       let rootProps = getRootProps();

       <div
         className={Cn.fromList([
           className,
           Cn.on(Styles.dragActive, isDragActive),
         ])}
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
