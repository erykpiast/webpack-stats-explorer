module Styles = {
  open Css;

  let arrowSize = px(200);

  let root =
    style([position(`relative), display(`flex), alignItems(`center)]);

  let arrow = style([height(arrowSize), width(arrowSize)]);

  let arrowLeft = style([transform(rotate(deg(45.0))), order(1)]);

  let arrowRight = style([transform(rotate(deg(135.0))), order(2)]);

  let label = style([fontSize(Theme.Size.Text.big)]);

  let labelLeft = style([order(2), textAlign(`left)]);

  let labelRight = style([order(1), textAlign(`right)]);

  let credit =
    style([
      position(`absolute),
      fontSize(px(12)),
      textAlign(`right),
      textDecoration(`none),
      color(Theme.Color.Text.primary),
    ]);

  let creditLeft = style([top(px(75)), left(px(175))]);

  let creditRight = style([top(px(150)), right(px(65))]);
};

type direction =
  | ToLeft
  | ToRight;

let copyright = {js|©|js};

[@react.component]
let make = (~className="", ~direction=ToLeft, ~children) => {
  let (
    arrowDirectionClassName,
    labelDirectionClassName,
    creditDirectionClassName,
  ) =
    switch (direction) {
    | ToLeft => (Styles.arrowLeft, Styles.labelLeft, Styles.creditLeft)
    | ToRight => (Styles.arrowRight, Styles.labelRight, Styles.creditRight)
    };

  <div className={Cn.make([className, Styles.root])}>
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
      className={Cn.make([Styles.credit, creditDirectionClassName])}
      href="https://www.flaticon.com/authors/freepik"
      title="Icon made by Freepik from www.flaticon.com">
      {copyright |> React.string}
    </a>
    <p className={Cn.make([Styles.label, labelDirectionClassName])}>
      children
    </p>
  </div>;
};