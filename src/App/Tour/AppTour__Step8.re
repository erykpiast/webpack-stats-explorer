module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"The tab selected by default is called " |> React.string}
      <code> {"Stat" |> React.string} </code>
      {". It shows code processed by
       loaders (like Babel) but not yet minified. That's why stat size is bigger
       than the one presented on the sidebar, which is..."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-size-stat",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=[
          "app",
          "node_modules",
          "regenerator-runtime",
          "runtime.js",
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
