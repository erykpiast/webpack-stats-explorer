module Styles = {
  open Css;

  let root =
    style([
      alignItems(`center),
      display(`flex),
      flexDirection(`column),
      fontSize(em(2.0)),
      height(`percent(100.0)),
      justifyContent(`center),
      position(`relative),
      width(`percent(100.0))
    ]);
  let arrow =
    style([
      position(`absolute),
      left(Theme.Space.double),
      top(Theme.Space.double),
    ]);
  let size = style([display(`block), color(Theme.Color.Text.secondary)]);
  let count = style([color(Theme.Color.Text.primary), margin(px(0))]);
  let diff = style([display(`block)]);
  let name = style([marginTop(px(0))]);
};

[@react.component]
let make = (~size, ~level, ~name="", ~count) => {
  let (one, many) = switch (level) {
  | `top => (L10N.chunk, L10N.chunks)
  | `chunk => (L10N.module_, L10N.modules)
  | `module_ => (L10N.module_, L10N.modules)
  };

  <section className=Styles.root>
    {String.length(name) > 0
      ? <h2 className=Styles.name>
      {name |> React.string}
    </h2>
      : React.null}
    <p className=Styles.count>
      {count |> Utils.pluralize(one, many) |> React.string}
    </p>
    <Size className=Styles.size value={snd(size)} />
    <NumericDiff
      className=Styles.diff
      after={snd(size)}
      before={fst(size)}
    />
  </section>;
};