module Styles = {
  open Css;

  let root =
    ReactDOMRe.Style.make(
      ~padding=px(0) |> Types.Length.toString,
      ~margin=px(0) |> Types.Length.toString,
      ~marginLeft=Theme.Space.half |> Types.Length.toString,
      (),
    );

  let lineNumberContainer =
    ReactDOMRe.Style.make(
      ~backgroundColor=Theme.Color.Background.bright |> Types.Color.toString,
      ~paddingLeft=Calc.(Theme.Space.double - Theme.Space.half) |> Types.Length.toString,
      ~paddingRight=Theme.Space.double |> Types.Length.toString,
      ~marginRight=Theme.Space.double |> Types.Length.toString,
      ~minHeight=`percent(100.0) |> Types.Length.toString,
      ~float=`left |> Types.Float.toString,
      ~textAlign=`right |> Types.TextAlign.toString,
      (),
    );

  let default = style([paddingLeft(Theme.Space.double), display(`block)]);

  let removed = style([backgroundColor(Theme.Color.Removed.background)]);

  let added = style([backgroundColor(Theme.Color.Added.background)]);
};

[@react.component]
let make =
    (~className="", ~diffMap=?, ~children) => {
  let defaultClassName = Styles.default;
  let addedClassName = Cn.make([Styles.default, Styles.added]);
  let removedClassName = Cn.make([Styles.default, Styles.removed]);
  let lineProps = switch (diffMap) {
    | Some(diffMap) => `Factory((lineNumber) => {
      let className = JsDiff.(
        switch (lineNumber |> diffMap) {
        | Intact(_) => defaultClassName
        | Added(_) => addedClassName
        | Removed(_) => removedClassName
        }
      );

      ReactDOMRe.props(~className=className, ());
    })
    | None => `Plain(ReactDOMRe.props(()))
  };

  <ReactSyntaxHighlighter.Prism
    language=`JavaScript
    showLineNumbers=true
    className
    customStyle=Styles.root
    lineProps
    wrapLines=true
    lineNumberContainerProps={ReactDOMRe.props(
      ~style=Styles.lineNumberContainer,
      (),
    )}>
    children
  </ReactSyntaxHighlighter.Prism>;
};