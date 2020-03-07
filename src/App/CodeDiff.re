module Styles = {
  open Css;

  let preStyle =
    ReactDOMRe.Style.make(
      ~padding=px(0) |> Types.Length.toString,
      ~margin=px(0) |> Types.Length.toString,
      ~background="none",
      (),
    );

  let wordDiff = [padding(px(0))];

  let contentText = [important(lineHeight(`initial))];

  let getContent = columnNumber => [
    borderSpacing(px(0)),
    padding(px(0)),
    position(`relative),
    after(
      switch (columnNumber) {
      | 0 => []
      | _ => [
          contentRule(`text("")),
          position(`absolute),
          left(ch(float_of_int(columnNumber))),
          top(px(0)),
          bottom(px(0)),
          width(px(1)),
          backgroundColor(Theme.Color.Border.default),
          fontSize(Theme.Size.Text.default),
          fontFamilies([
            `custom("Consolas"),
            `custom("Monaco"),
            `custom("Andale Mono"),
            `custom("Ubuntu Mono"),
            `monospace,
          ]),
        ]
      },
    ),
  ];

  let lineNumber = [fontSize(Theme.Size.Text.default)];

  let gutter = [
    padding(px(0)),
    padding2(~h=Theme.Space.double, ~v=px(0)),
    borderSpacing(px(0)),
    minWidth(px(0)),
  ];

  let diffContainer = [
    zIndex(-1),
    selector(
      "pre",
      [important(lineHeight(`initial)), important(opacity(1.0))],
    ),
  ];
};

[@react.component]
let make = (~after, ~before, ~columnGuideline, ~className) => {
  let renderContent = content =>
    <ReactSyntaxHighlighter.Prism
      language=`JavaScript
      showLineNumbers=false
      customStyle=Styles.preStyle
      wrapLines=true
      _PreTag={`intrinsic("span")}>
      content
    </ReactSyntaxHighlighter.Prism>;
  <ReactDiffViewer
    oldValue=before
    newValue=after
    compareMethod=`words
    splitView=false
    showDiffOnly=false
    renderContent
    styles={ReactDiffViewer.Styles.make(
      ~wordDiff=Styles.wordDiff,
      ~content=Styles.getContent(columnGuideline),
      ~contentText=Styles.contentText,
      ~lineNumber=Styles.lineNumber,
      ~gutter=Styles.gutter,
      ~diffContainer=Styles.diffContainer,
      (),
    )}
  />;
};