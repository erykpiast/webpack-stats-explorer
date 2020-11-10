module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"The only reason of the " |> React.string}
      <code> {"index.js" |> React.string} </code>
      {" module is " |> React.string}
      <code> {"app.js" |> React.string} </code>
      {" in the " |> React.string}
      <code> {"src" |> React.string} </code>
      {" directory. It looks familiar - it's actually our code!"
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
          "regenerator",
          "index.js",
        ],
        ~tab=1,
        ~splitView=false,
        ~timeline=false,
        ~index=0,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: false,
    navDotAriaLabel: "",
  };
