open Rationale.Option.Infix;
open Rationale.Function.Infix;

module CompareMethod = {
  [@bs.deriving jsConverter]
  type t_ = [
    | [@bs.as "diffChars"] `chars
    | [@bs.as "diffWords"] `words
    | [@bs.as "diffWordsWithSpace"] `wordsWithSpace
    | [@bs.as "diffLines"] `lines
    | [@bs.as "diffTrimmedLines"] `trimmedLines
    | [@bs.as "diffSentences"] `sentences
    | [@bs.as "diffCss"] `css
  ];

  type t = t_;

  let toString = t_ToJs;
}

module Side = {
  [@bs.deriving jsConverter]
  type t_ = [
    | [@bs.as "L"] `left
    | [@bs.as "R"] `right
  ];

  type t = t_;

  let toString = t_ToJs;
}

module LineHighlight = {
  type t = (Side.t, int);

  let toString = (line) => (line |> fst |> Side.toString) ++ (line |> snd |> string_of_int);
}

module ThemeColors = {
  [@bs.deriving abstract]
  type t = {
    diffViewerBackground: string,
    diffViewerColor: string,
    addedBackground: string,
    addedColor: string,
    removedBackground: string,
    removedColor: string,
    wordAddedBackground: string,
    wordRemovedBackground: string,
    addedGutterBackground: string,
    removedGutterBackground: string,
    gutterBackground: string,
    gutterBackgroundDark: string,
    highlightBackground: string,
    highlightGutterBackground: string,
    codeFoldGutterBackground: string,
    codeFoldBackground: string,
    emptyLineBackground: string,
    gutterColor: string,
    addedGutterColor: string,
    removedGutterColor: string,
    codeFoldContentColor: string,
    diffViewerTitleBackground: string,
    diffViewerTitleColor: string,
    diffViewerTitleBorderColor: string
  };

  let make = t;
};

module Styles = {
  [@bs.deriving abstract]
  type t = {
    [@bs.optional] variables: ThemeColors.t,
    [@bs.optional] diffContainer: Js.Json.t,
    [@bs.optional] diffRemoved: Js.Json.t,
    [@bs.optional] diffAdded: Js.Json.t,
    [@bs.optional] marker: Js.Json.t,
    [@bs.optional] emptyGutter: Js.Json.t,
    [@bs.optional] highlightedLine: Js.Json.t,
    [@bs.optional] lineNumber: Js.Json.t,
    [@bs.optional] highlightedGutter: Js.Json.t,
    [@bs.optional] contentText: Js.Json.t,
    [@bs.optional] gutter: Js.Json.t,
    [@bs.optional] line: Js.Json.t,
    [@bs.optional] wordDiff: Js.Json.t,
    [@bs.optional] wordAdded: Js.Json.t,
    [@bs.optional] wordRemoved: Js.Json.t,
    [@bs.optional] codeFoldGutter: Js.Json.t,
    [@bs.optional] emptyLine: Js.Json.t,
    [@bs.optional] content: Js.Json.t,
    [@bs.optional] titleBlock: Js.Json.t,
    [@bs.optional] splitView: Js.Json.t,
  };

  let make = (
    ~variables=?,
    ~diffContainer=?,
    ~diffRemoved=?,
    ~diffAdded=?,
    ~marker=?,
    ~emptyGutter=?,
    ~highlightedLine=?,
    ~lineNumber=?,
    ~highlightedGutter=?,
    ~contentText=?,
    ~gutter=?,
    ~line=?,
    ~wordDiff=?,
    ~wordAdded=?,
    ~wordRemoved=?,
    ~codeFoldGutter=?,
    ~emptyLine=?,
    ~content=?,
    ~titleBlock=?,
    ~splitView=?,
    (),
  ) => t(
    ~variables?,
    ~diffContainer=?(diffContainer <$> Css.toJson),
    ~diffRemoved=?(diffRemoved <$> Css.toJson),
    ~diffAdded=?(diffAdded <$> Css.toJson),
    ~marker=?(marker <$> Css.toJson),
    ~emptyGutter=?(emptyGutter <$> Css.toJson),
    ~highlightedLine=?(highlightedLine <$> Css.toJson),
    ~lineNumber=?(lineNumber <$> Css.toJson),
    ~highlightedGutter=?(highlightedGutter <$> Css.toJson),
    ~contentText=?(contentText <$> Css.toJson),
    ~gutter=?(gutter <$> Css.toJson),
    ~line=?(line <$> Css.toJson),
    ~wordDiff=?(wordDiff <$> Css.toJson),
    ~wordAdded=?(wordAdded <$> Css.toJson),
    ~wordRemoved=?(wordRemoved <$> Css.toJson),
    ~codeFoldGutter=?(codeFoldGutter <$> Css.toJson),
    ~emptyLine=?(emptyLine <$> Css.toJson),
    ~content=?(content <$> Css.toJson),
    ~titleBlock=?(titleBlock <$> Css.toJson),
    ~splitView=?(splitView <$> Css.toJson),
    (),
  );
}

[@bs.module "react-diff-viewer"] [@react.component]
external make:
(
  ~oldValue: string=?,
  ~newValue: string=?,
  ~splitView: bool=?,
  ~disableWordDiff: bool=?,
  ~compareMethod: string=?,
  ~hideLineNumbers: bool=?,
  ~renderContent: (string => React.element)=?,
  ~onLineNumberClick: (string => unit)=?,
  ~highlightLines: array(string)=?,
  ~showDiffOnly: bool=?,
  ~extraLinesSurroundingDiff: int=?,
  ~codeFoldMessageRenderer: (int => string)=?,
  ~styles: Styles.t=?,
  ~useDarkTheme: bool=?,
  ~leftTitle: string=?,
  ~rightTitle: string=?
 ) => React.element = "default";

 let makeProps = (
  ~oldValue=?,
  ~newValue=?,
  ~splitView=?,
  ~disableWordDiff=?,
  ~compareMethod=?,
  ~hideLineNumbers=?,
  ~renderContent=?,
  ~onLineNumberClick=?,
  ~highlightLines=?,
  ~showDiffOnly=?,
  ~extraLinesSurroundingDiff=?,
  ~codeFoldMessageRenderer=?,
  ~styles=?,
  ~useDarkTheme=?,
  ~leftTitle=?,
  ~rightTitle=?
 ) => makeProps(
  ~oldValue?,
  ~newValue?,
  ~splitView?,
  ~disableWordDiff?,
  ~compareMethod=?(compareMethod <$> CompareMethod.toString),
  ~hideLineNumbers?,
  ~renderContent?,
  ~onLineNumberClick?,
  ~highlightLines=?(highlightLines <$> (List.map(LineHighlight.toString) ||> Array.of_list)),
  ~showDiffOnly?,
  ~extraLinesSurroundingDiff?,
  ~codeFoldMessageRenderer?,
  ~styles?,
  ~useDarkTheme?,
  ~leftTitle?,
  ~rightTitle?
);
