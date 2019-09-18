module Styles = {
  open Css;

  let root = style([display(`flex)]);

  let tab =
    style([
      alignItems(`center),
      backgroundColor(`transparent),
      borderStyle(`none),
      borderRadius(px(0)),
      boxSizing(`borderBox),
      cursor(`pointer),
      display(`inlineFlex),
      flexShrink(0.0),
      justifyContent(`center),
      letterSpacing(em(0.02857)),
      lineHeight(`abs(1.75)),
      margin(px(0)),
      maxWidth(Theme.Space.doublehexfold),
      minHeight(Theme.Space.triple),
      minWidth(Theme.Space.quadruple),
      outlineStyle(`none),
      overflow(`hidden),
      padding2(~v=Theme.Space.default, ~h=Theme.Space.double),
      position(`relative),
      textAlign(`center),
      textDecoration(`none),
      textTransform(`uppercase),
      userSelect(`none),
      verticalAlign(`middle),
      whiteSpace(`normal),
    ]);

  let selectedTab =
    style([
      opacity(1.0),
      borderBottom(px(2), `solid, Theme.Color.Border.accent),
    ]);
};

let component = ReasonReact.statelessComponent("Tabs");

let notNullElement = (!==)(ReasonReact.null);

let make = (~className="", ~selectedIndex=0, children) => {
  ...component,
  render: _self => {
    <div className={Cn.make([className, Styles.root])}>
      ...{
           children
           |> Array.mapi((index, child) =>
                if (child === ReasonReact.null) {
                  ReasonReact.null;
                } else {
                  <button
                    className={Cn.make([
                      Styles.tab,
                      Cn.ifTrue(Styles.selectedTab, index === selectedIndex),
                    ])}>
                    child
                  </button>;
                }
              )
         }
    </div>;
  },
};