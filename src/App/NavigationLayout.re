module Styles = {
  open Css;

  let wrapper = style([
    display(`flex),
    width(`percent(100.0)),
  ]);

  let column = style([
    display(block),
    width(`percent(50.0)),
  ]);
};

let component = ReasonReact.statelessComponent("NavigationLayout");

let make = (~side, ~main, _children) => {
  ...component,
  render: (_self) => {
    <div className=Styles.wrapper>
      <div className=Styles.column>
        {side}
      </div>
      <div className=Styles.column>
        {main}
      </div>
    </div>
  }
};