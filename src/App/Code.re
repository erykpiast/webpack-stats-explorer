module Styles = {
  open Css;

  let (+) = Calc.(+);
  let (-) = Calc.(-);

  let counterName = "line-number";

  let lineNumberLeftMargin = Theme.Space.half;
  let lineNumberLeftPadding = Theme.Space.double - Theme.Space.half;
  let lineNumberRightPadding = Theme.Space.double;
  let lineNumberRightMargin = Theme.Space.double;

  let rootStyle =
    ReactDOMRe.Style.make(
      ~backgroundColor=Theme.Color.Background.code |> Types.Color.toString,
      ~padding=px(0) |> Types.Length.toString,
      ~margin=px(0) |> Types.Length.toString,
      ~marginLeft=lineNumberLeftMargin |> Types.Length.toString,
      ~counterReset=
        Types.CounterReset.reset(counterName) |> Types.CounterReset.toString,
      ~overflow=`auto |> Types.Overflow.toString,
      (),
    );

  let rootClassName =
    style([
      selector(
        "code",
        [
          display(`flex),
          flexDirection(`column),
          width(`maxContent),
          minHeight(`percent(100.0)),
          minWidth(ch(120.0)),
        ],
      ),
    ]);

  let getLineClassName = (lineNumberWidth, columnNumber) => {
    style([
      display(`block),
      flexShrink(0.0),
      flexGrow(0.0),
      whiteSpace(`nowrap),
      position(`relative),
      before([
        backgroundColor(Theme.Color.Background.bright),
        color(Theme.Color.Text.primary),
        contentRule(Types.Counter.counter(counterName)),
        display(`inlineBlock),
        paddingLeft(lineNumberLeftPadding),
        paddingRight(lineNumberRightPadding),
        marginRight(lineNumberRightMargin),
        width(ch(float_of_int(lineNumberWidth))),
        textAlign(`right),
        position(`relative),
        zIndex(1),
      ]),
      after(
        switch (columnNumber) {
        | 0 => []
        | _ => [
            contentRule(`text("")),
            position(`absolute),
            left(
              ch(float_of_int(lineNumberWidth))
              + ch(float_of_int(columnNumber))
              + lineNumberLeftMargin
              + lineNumberLeftPadding
              + lineNumberRightPadding
              + lineNumberRightMargin,
            ),
            top(px(0)),
            bottom(px(0)),
            width(px(1)),
            backgroundColor(Theme.Color.Border.default),
          ]
        },
      ),
      selector(
        "&:last-of-type",
        [
          flexGrow(1.0),
          before([
            boxShadow(
              Shadow.box(
                ~x=vh(-50.0),
                ~y=vh(50.0),
                ~spread=vh(50.0),
                Theme.Color.Background.bright,
              ),
            ),
          ]),
        ],
      ),
    ]);
  };

  module LineNumberContainer = {
    let leftPadding = Theme.Space.double - Theme.Space.half;
    let rightPadding = Theme.Space.double;
    let rightMargin = Theme.Space.double;
    let style =
      ReactDOMRe.Style.make(
        ~backgroundColor=Theme.Color.Background.bright |> Types.Color.toString,
        ~paddingLeft=leftPadding |> Types.Length.toString,
        ~paddingRight=rightPadding |> Types.Length.toString,
        ~marginRight=rightMargin |> Types.Length.toString,
        ~minHeight=`percent(100.0) |> Types.Length.toString,
        ~float=`left |> Types.Float.toString,
        ~textAlign=`right |> Types.TextAlign.toString,
        ~position=`sticky |> Types.Position.toString,
        ~left=px(0) |> Types.Length.toString,
        (),
      );
  };
};

let getTheGreatestLineNumberLength =
  Rationale.Function.Infix.(
    Utils.String.split("\n")
    ||> Array.length
    ||> string_of_int
    ||> Js.String.length
  );

[@react.component]
let make =
    (~className="", ~columnGuideline=0, ~language=`JavaScript, ~children) => {
  let theGreatestLineNumberLength = getTheGreatestLineNumberLength(children);

  let lineProps =
    `Plain(
      ReactDOMRe.props(
        ~className=
          Styles.getLineClassName(
            theGreatestLineNumberLength,
            columnGuideline,
          ),
        ~style=
          ReactDOMRe.Style.make(
            ~counterIncrement=
              Css.Types.CounterIncrement.increment(
                Styles.counterName,
                ~value=1,
              )
              |> Css.Types.CounterIncrement.toString,
            (),
          ),
        (),
      ),
    );

  <ReactSyntaxHighlighter.Prism
    language
    showLineNumbers=false
    className={Cn.make([className, Styles.rootClassName])}
    customStyle=Styles.rootStyle
    lineProps
    wrapLines=true>
    children
  </ReactSyntaxHighlighter.Prism>;
};