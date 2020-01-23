module Styles = {
  open Css;

  let counterName = "line-number";

  let rootStyle =
    ReactDOMRe.Style.make(
      ~padding=px(0) |> Types.Length.toString,
      ~margin=px(0) |> Types.Length.toString,
      ~marginLeft=Theme.Space.half |> Types.Length.toString,
      ~counterReset=
        Types.CounterOperation.reset(counterName)
        |> Types.CounterOperation.toString,
      (),
    );

  let getLineClassName = (lineNumberWidth, columnNumber) => {
    let lineNumberLeftPadding = Calc.(Theme.Space.double - Theme.Space.half);
    let lineNumberRightPadding = Theme.Space.double;
    let lineNumberRightMargin = Theme.Space.double;

    style([
      display(`block),
      whiteSpace(`preWrap),
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
      ]),
      after(
        switch (columnNumber) {
        | 0 => []
        | _ => [
            contentRule(`string("")),
            position(`absolute),
            left(Calc.(
              ch(float_of_int(lineNumberWidth)) +
              ch(float_of_int(columnNumber)) +
              lineNumberLeftPadding +
              lineNumberRightPadding +
              lineNumberRightMargin
            )),
            top(px(0)),
            bottom(px(0)),
            width(px(1)),
            backgroundColor(Theme.Color.Border.default),
          ]
        },
      ),
    ]);
  };

  module LineNumberContainer = {
    let leftPadding = Calc.(Theme.Space.double - Theme.Space.half);
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

[@react.component]
let make = (~className="", ~columnGuideline=0, ~children) => {
  let theGreatestLineNumberLength =
    children
    |> Utils.String.split("\n")
    |> Array.length
    |> string_of_int
    |> Js.String.length;

  let lineProps =
    `Plain(
      ReactDOMRe.props(
        ~className=Styles.getLineClassName(theGreatestLineNumberLength, columnGuideline),
        ~style=
          ReactDOMRe.Style.make(
            ~counterIncrement=
              Css.Types.CounterOperation.increment(
                Styles.counterName,
                ~value=1,
              )
              |> Css.Types.CounterOperation.toString,
            (),
          ),
        (),
      ),
    );

  <ReactSyntaxHighlighter.Prism
    language=`JavaScript
    showLineNumbers=false
    className
    customStyle=Styles.rootStyle
    lineProps
    wrapLines=true>
    children
  </ReactSyntaxHighlighter.Prism>;
};