module Styles = {
  open Css;

  let arrowSize = px(200);

  let root =
    style([position(`relative), display(`flex), alignItems(`center)]);

  let rootSide = style([flexDirection(`row)]);

  let rootBelow = style([flexDirection(`column)]);

  let arrow = style([height(arrowSize), width(arrowSize)]);

  let arrowSide = style([transform(rotate(deg(45.0))), order(1)]);

  let arrowBelow =
    style([transforms([rotate(deg(25.0)), scaleY(-1.0)]), order(2)]);

  let label = style([fontSize(Theme.Size.Text.big), order(2)]);

  let labelSide = style([]);

  let labelBelow =
    style([margin(px(0)), marginTop(px(- Theme.Space.Raw.double))]);

  let credit =
    style([
      position(`absolute),
      fontSize(px(12)),
      textAlign(`right),
      textDecoration(`none),
      color(Theme.Color.Text.primary),
      top(px(150)),
      right(px(150)),
    ]);

  let creditSide = style([]);

  let creditBelow = style([right(`unset)]);
};

let copyright = {js|©|js};

[@react.component]
let make = (~className="", ~mode=`side, ~children) => {
  let (
    arrowDirectionClassName,
    labelDirectionClassName,
    creditClassName,
    rootClassName,
  ) =
    switch (mode) {
    | `side => (
        Styles.arrowSide,
        Styles.labelSide,
        Styles.creditSide,
        Styles.rootSide,
      )
    | `below => (
        Styles.arrowBelow,
        Styles.labelBelow,
        Styles.creditBelow,
        Styles.rootBelow,
      )
    };

  <div className={Cn.make([className, rootClassName, Styles.root])}>
    <svg
      xmlns="http://www.w3.org/2000/svg"
      width="380.1"
      height="380.1"
      viewBox="0 0 380.1 380.1"
      className={Cn.make([Styles.arrow, arrowDirectionClassName])}>
      <path
        d="M379.6 148.3c-.6-7.4-10.4-9.2-13.4-3.7-9.8-6.1-22.7-10.4-31.9-15.3-15.3-8-31.8-16.5-49-21.4-3.6-5.5-14-3.7-13.4 4.3 1.9 91.8-115.6 90-181.1 79 0-7.4.6-14.8.6-21.5v-9.2c0-1.8-3-7.3-3-4.9 0-.6-.7-1.2-.7-1.8-6.7-19-79.6 29.4-86.9 41.6A7.5 7.5 0 0 0 2 204c1.3.6 2.5 1.8 3 3-.5 1.2-.5 2.5-.5 3 .6 8 9.8 15.4 14.7 20.3a407.2 407.2 0 0 0 47.7 44c2.4 1.9 7.3 1.3 9.2-1.2.6-.6.6-1.2 1.2-1.2.6-.6.6-1.8.6-3 .6-.7 1.2-1.9 1.9-3.1.6-7.4.6-16.6 3-23.3 0-.6.6-1.2.6-1.8 88.2 42.2 308.5 42.2 296.2-92.4zm-298 78.3H79c-9.8 0-8.5 19-7.3 30-9.8-8-19-17.1-28.2-25.7a277.2 277.2 0 0 1-19-19c-1.8-2.4-4.2-4.3-6-6.7a16.3 16.3 0 0 0-3.7-3c-1.2-.7-1.9-.7-1.9-.7l-.6-.6c5-3.7 12.3-9.8 13.5-10.4 9.2-6.1 18.4-11 28.1-16 3.7-1.8 16-5.4 25.1-10.3v1.8c-1.2 8-2.4 16-2.4 24.5 0 5.5 4.3 7.3 8 7.3 68.5 29.4 198.2 13.5 202.5-77.7 13.5 6.7 26.3 13.5 39.8 20.8 9.8 5.5 26.3 17.8 39.2 19-7.4 119.3-210 89.4-284.6 66.7z"
      />
    </svg>
    <a
      className={Cn.make([Styles.credit, creditClassName])}
      href="https://www.flaticon.com/authors/freepik"
      title="Icon made by Freepik from www.flaticon.com">
      {copyright |> React.string}
    </a>
    <p className={Cn.make([Styles.label, labelDirectionClassName])}>
      children
    </p>
  </div>;
};