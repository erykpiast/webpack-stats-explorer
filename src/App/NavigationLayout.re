module Styles = {
  open Css;

  let headerHeight = Theme.Space.tenfold;

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
      width(`percent(100.0)),
    ]);

  let top =
    style([
      display(`flex),
      height(headerHeight),
      backgroundColor(Theme.Color.Background.default),
      flexShrink(0.0),
    ]);

  let contentWrapper =
    style([
      display(`flex),
      flexGrow(1.0),
      maxHeight(Calc.(`percent(100.0) - headerHeight)),
    ]);

  let side =
    style([
      display(`block),
      width(Theme.Space.triplehexteenfold),
      backgroundColor(Theme.Color.Background.default),
      maxHeight(`percent(100.0)),
      flexShrink(0.0),
    ]);

  let main =
    style([
      display(`flex),
      flexDirection(`column),
      flexGrow(1.0),
      boxShadow(
        Shadow.box(
          ~x=`px(0),
          ~y=`px(0),
          ~spread=`px(0),
          ~inset=true,
          ~blur=`px(4),
          Theme.Color.Shadow.default,
        ),
      ),
      overflowX(`hidden),
    ]);
};

[@react.component]
let make = (~side, ~main, ~top) => {
  <div className=Styles.wrapper>
    <div className=Styles.top> top </div>
    <div className=Styles.contentWrapper>
      <div className=Styles.side> side </div>
      <div className=Styles.main> main </div>
    </div>
  </div>;
};