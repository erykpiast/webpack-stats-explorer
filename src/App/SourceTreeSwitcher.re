module Styles = {
  open Css;

  let root =
    style([
      marginTop(`auto),
      display(`flex),
      flexDirection(`row),
    ]);

  let button =
    style([
      margin(px(0)),
      flexGrow(1.0),
      borderRadius(px(0)),
      boxShadow(`none),
    ]);

  let selectedButton =
    style([color(Theme.Color.Text.primary), background(`none)]);
};

[@react.component]
let make = (~className="", ~selected=true, ~onSwitch) => {
  <div className={Cn.make([className, Styles.root])}>
    <Button
      disabled=selected
      onClick={_ => onSwitch()}
      className={Cn.make([
        Styles.button,
        Cn.ifTrue(Styles.selectedButton, selected),
      ])}>
      {L10N.treeView |> React.string}
    </Button>
    <Button
      disabled={!selected}
      onClick={_ => onSwitch()}
      className={Cn.make([
        Styles.button,
        Cn.ifTrue(Styles.selectedButton, !selected),
      ])}>
      {L10N.moduleListView |> React.string}
    </Button>
  </div>;
};