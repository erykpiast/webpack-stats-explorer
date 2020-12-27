module Styles = {
  open Css;

  let root = style([display(`flex)]);

  let tab =
    style([
      alignItems(`center),
      backgroundColor(`transparent),
      borderStyle(`none),
      borderBottom(px(2), `solid, `transparent),
      borderRadius(px(0)),
      boxSizing(`borderBox),
      cursor(`pointer),
      display(`inlineFlex),
      flexShrink(0.0),
      fontSize(rem(1.0)),
      fontFamily(`inherit_),
      flexGrow(1.0),
      justifyContent(`center),
      letterSpacing(em(0.02857)),
      lineHeight(`abs(1.75)),
      margin(px(0)),
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

[@react.component]
let make = (~className="", ~selectedIndex=0, ~onChange=_ => (), ~id="", ~children) => {
  <div className={Cn.fromList([className, Styles.root])} id>
    {children
     |> Array.mapi((index, child) =>
          if (child === React.null) {
            React.null;
          } else {
            <button
              className={Cn.fromList([
                Styles.tab,
                Cn.on(Styles.selectedTab, index === selectedIndex),
              ])}
              onClick={_event => onChange(index)}
              key={index |> string_of_int}>
              child
            </button>;
          }
        )
     |> React.array}
  </div>;
};
