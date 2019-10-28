module Styles = {
  open Css;

  let button =
    style([
      borderWidth(px(0)),
      borderRadius(Theme.Space.half),
      boxShadows([
        Shadow.box(
          ~y=px(0),
          ~x=px(1),
          ~blur=px(5),
          ~spread=px(0),
          Theme.Color.Shadow.Button.primary,
        ),
        Shadow.box(
          ~y=px(0),
          ~x=px(2),
          ~blur=px(2),
          ~spread=px(0),
          Theme.Color.Shadow.Button.secondary,
        ),
        Shadow.box(
          ~y=px(0),
          ~x=px(3),
          ~blur=px(1),
          ~spread=px(-2),
          Theme.Color.Shadow.Button.tertiary,
        ),
      ]),
      cursor(`pointer),
      lineHeight(`em(1.75)),
      margin(Theme.Space.default),
      padding2(~v=Theme.Space.default, ~h=Theme.Space.double),
      textTransform(`uppercase),
    ]);

  let default = style([backgroundColor(Theme.Color.Background.button)]);

  let primary =
    style([
      backgroundColor(Theme.Color.Background.primaryButton),
      color(Theme.Color.Text.contrast),
    ]);
};

type type_ =
  | Default
  | Primary;

[@react.component]
let make = (~onClick=_ => (), ~className="", ~type_=Default, ~children) => {
  let typeClassName =
    Cn.mapSome(Some(type_), t =>
      switch (t) {
      | Default => Styles.default
      | Primary => Styles.primary
      }
    );
  let className = Cn.make([Styles.button, typeClassName, className]);

  <button className onClick> children </button>;
};