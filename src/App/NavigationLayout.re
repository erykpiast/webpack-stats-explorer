module Styles = {
  open Css;

  let headerHeight = Theme.Space.tenfold;

  let root =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
      width(`percent(100.0)),
    ]);

  let topSection =
    style([
      display(`flex),
      height(headerHeight),
      backgroundColor(Theme.Color.Background.default),
      flexShrink(0.0),
      alignItems(`center),
    ]);

  let aboveTop = style([]);

  let contentWrapper =
    style([
      display(`flex),
      flexGrow(1.0),
      minHeight(px(0)),
      overflowY(`hidden),
    ]);

  let getSideSection = isSidebarCollapsed =>
    style([
      display(`block),
      width(
        isSidebarCollapsed
          ? Theme.Space.octafold : Theme.Space.triplehexteenfold,
      ),
      backgroundColor(Theme.Color.Background.default),
      maxHeight(`percent(100.0)),
      overflow(`hidden),
      flexShrink(0.0),
      position(`relative),
      transition(
        ~duration=250,
        ~timingFunction=`easeInOut,
        "width",
      ),
    ]);

  let getSideToggle = isSidebarCollapsed =>
    style([
      width(Theme.Space.double),
      bottom(px(0)),
      position(`absolute),
      top(px(0)),
      right(px(0)),
      display(`flex),
      flexDirection(`column),
      justifyContent(`center),
      transition(
        ~duration=250,
        ~timingFunction=`easeInOut,
        "background-color",
      ),
      after([
        contentRule(`text(isSidebarCollapsed ? {js|▶|js} : {js|◀|js})),
        color(Theme.Color.Text.secondary),
        transition(~duration=250, ~timingFunction=`easeInOut, "color"),
      ]),
      hover([
        backgroundColor(Theme.Color.Background.selected),
        cursor(`pointer),
        after([color(Theme.Color.Text.primary)]),
      ]),
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
let make =
    (~side, ~main, ~top, ~aboveTop, ~isSidebarCollapsed, ~onSidebarToggle) => {
  <div className=Styles.root>
    <div className=Styles.aboveTop> aboveTop </div>
    <div className=Styles.topSection> top </div>
    <div className=Styles.contentWrapper>
      <div className={Styles.getSideSection(isSidebarCollapsed)}>
        side
        <div
          className={Styles.getSideToggle(isSidebarCollapsed)}
          onClick={_ => onSidebarToggle()}
        />
      </div>
      <div className=Styles.main> main </div>
    </div>
  </div>;
};
