module Styles = {
  open Css;

  let root = style([]);
}

[@react.component]
let make = (~onClick) => {
  <Button onClick type_=Button.Primary>
    {"+" |> React.string}
  </Button>;
};