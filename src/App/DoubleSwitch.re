module Styles = {
  open Css;

  let button = style([margin(px(0)), lineHeight(`abs(0.5))]);

  let aButton =
    style([borderTopRightRadius(px(0)), borderBottomRightRadius(px(0))]);

  let bButton =
    style([borderTopLeftRadius(px(0)), borderBottomLeftRadius(px(0))]);
};

[@react.component]
let make = (~a, ~b, ~current, ~onSwitch, ~className="", ~id="") => {
  let renderSwitchButton = (value, className) => {
    let active = current === fst(value);
    <Button
      onClick={_ => value |> fst |> onSwitch}
      disabled=active
      className={Cn.fromList([className, Styles.button])}>
      {value |> snd |> React.string}
    </Button>;
  };

  <div className id>
    {renderSwitchButton(a, Styles.aButton)}
    {renderSwitchButton(b, Styles.bButton)}
  </div>;
};
