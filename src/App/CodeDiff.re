type mode =
  | Unified
  | Split;

module Styles = {
  open Css;

  let codeFontFamily =
    fontFamilies([
      `custom("Consolas"),
      `custom("Monaco"),
      `custom("Andale Mono"),
      `custom("Ubuntu Mono"),
      `monospace,
    ]);

  let preStyle =
    ReactDOMRe.Style.make(
      ~padding=px(0) |> Types.Length.toString,
      ~margin=px(0) |> Types.Length.toString,
      ~background="none",
      (),
    );

  let wordDiff = [padding(px(0))];

  let contentText = [important(lineHeight(`initial))];

  let getBackgroundLayer = color =>
    before([
      contentRule(`text("")),
      backgroundColor(color),
      position(`absolute),
      left(px(0)),
      right(px(0)),
      top(px(0)),
      height(px(100)),
    ]);

  let getContent = (mode, columnGuideline) =>
    [
      display(`block),
      borderSpacing(px(0)),
      flexGrow(1.0),
      flexShrink(0.0),
      padding(px(0)),
      position(`relative),
    ]
    |> List.append(
         switch (columnGuideline) {
         | 0 => []
         | _ => [
             selector(
               "pre",
               [minWidth(ch(float_of_int(columnGuideline)))],
             ),
             width(`auto),
             before([
               contentRule(`text("")),
               backgroundColor(Theme.Color.Border.default),
               display(`block),
               position(`absolute),
               left(ch(float_of_int(columnGuideline))),
               bottom(px(0)),
               top(px(0)),
               right(px(0)),
               width(px(1)),
             ]),
           ]
         },
       )
    |> List.append(
         switch (mode) {
         | Unified => []
         | Split => [width(`percent(50.0)), minWidth(ch(80.0)), maxWidth(vw(60.9))]
         },
       );

  let line = [
    display(`flex),
    flexShrink(0.0),
    flexGrow(0.0),
    height(px(25)),
    selector("&:last-of-type", [flexGrow(1.0)]),
  ];

  let lineNumber = [
    fontSize(Theme.Size.Text.default),
    fontFamilies(Theme.FontFamily.code),
  ];

  let marker = [
    width(ch(1.0)),
    padding2(~v=px(0), ~h=Theme.Space.default),
    boxSizing(`contentBox),
    flexShrink(0.0),
  ];

  let getGutter = lineNumberWidth => [
    backgroundColor(Theme.Color.Background.bright),
    padding(px(0)),
    padding2(~h=Theme.Space.double, ~v=px(0)),
    borderSpacing(px(0)),
    width(ch(float_of_int(lineNumberWidth))),
    minWidth(px(0)),
    position(`relative),
    display(`block),
    boxSizing(`contentBox),
    flexShrink(0.0),
  ];

  let getColumnGuideline = (columnGuideline, lineNumberWidth) =>
    style([
      position(`absolute),
      left(px(0)),
      transform(
        translateX(
          Calc.(
            ch(float_of_int(lineNumberWidth * 3))
            + Theme.Space.octafold
            + ch(float_of_int(columnGuideline))
            + px(20)
          ),
        ),
      ),
      bottom(px(0)),
      top(px(0)),
      width(px(1)),
      backgroundColor(Theme.Color.Border.default),
      fontSize(Theme.Size.Text.default),
      codeFontFamily,
    ]);

  let diffContainer = [
    background(`none),
    codeFontFamily,
    display(`block),
    position(`relative),
    width(`percent(100.0)),
    zIndex(-1),
    selector(
      "tbody",
      [
        backgroundColor(Theme.Color.Background.code),
        display(`flex),
        flexDirection(`column),
        minHeight(`percent(100.0)),
        minWidth(`percent(100.0)),
        width(`maxContent),
      ],
    ),
    selector(
      "pre",
      [
        important(lineHeight(px(25))),
        important(opacity(1.0)),
        codeFontFamily,
      ],
    ),
  ];
};

[@react.component]
let make =
    (~after, ~before, ~columnGuideline, ~mode=Unified, ~language=`JavaScript) => {
  let greatestLineNumberWidth =
    [|
      Code.getTheGreatestLineNumberLength(after),
      Code.getTheGreatestLineNumberLength(before),
    |]
    |> Utils.Array.maxInt;
  let renderContent = content => {
    <ReactSyntaxHighlighter.Prism
      language
      showLineNumbers=false
      customStyle=Styles.preStyle
      wrapLines=true
      _PreTag={`intrinsic("span")}>
      {content |> Utils.defaultTo("")}
    </ReactSyntaxHighlighter.Prism>;
  };
  <>
    <ReactDiffViewer
      oldValue=before
      newValue=after
      compareMethod=`words
      splitView={
        switch (mode) {
        | Unified => false
        | Split => true
        }
      }
      showDiffOnly=false
      renderContent
      styles={ReactDiffViewer.Styles.make(
        ~wordDiff=Styles.wordDiff,
        ~content=Styles.getContent(mode, columnGuideline),
        ~contentText=Styles.contentText,
        ~line=Styles.line,
        ~lineNumber=Styles.lineNumber,
        ~gutter=Styles.getGutter(greatestLineNumberWidth),
        ~marker=Styles.marker,
        ~diffContainer=Styles.diffContainer,
        (),
      )}
    />
  </>;
};
