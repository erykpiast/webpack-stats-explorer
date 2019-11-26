open Rationale.Function.Infix;

module Styles = {
  open Css;

  let input = style([]);

  let label = style([backgroundColor(Theme.Color.Background.danger)]);
};

[@react.component]
let make = (~onFiles, ~label, ~className="", ~children) => {
  <ReactDropzone
    accept={ReactDropzone.Single("application/json")}
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
    {({getInputProps, getRootProps}) => {
       let inputProps = getInputProps();
       let rootProps = getRootProps();

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