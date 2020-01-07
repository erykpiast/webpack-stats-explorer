module Styles = {
  open Css;

  let root =
    ReactDOMRe.Style.make(
      ~padding="0px",
      ~marginLeft="4px",
      (),
    );

  let lineNumberContainer =
    ReactDOMRe.Style.make(
      ~backgroundColor="white",
      ~paddingLeft="12px",
      ~paddingRight="16px",
      ~marginRight="16px",
      ~minHeight="100%",
      ~float="left",
      ~textAlign="right",
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