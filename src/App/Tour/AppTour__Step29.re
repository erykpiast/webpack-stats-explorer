module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"Fortunately mitigating this issue is quite easy. It's enough to enable "
       |> React.string}
      <code> {"helpers" |> React.string} </code>
      {" option of " |> React.string}
      <code> {"babel-transform-runtime" |> React.string} </code>
      {" plugin. Instead of being inlined, each helper is then imported from its own module.
      Such imports cost almost nothing and are shared between different app modules."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=[
          "app",
          "node_modules",
          "@babel",
          "runtime",
          "helpers",
        ],
        ~tab=2,
        ~splitView=true,
        ~timeline=false,
        ~index=2,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
