module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"You can see all details of selected " |> React.string}
      <code> {"runtime.js" |> React.string} </code>
      {" here, in the right part of the screen. The top section contains
          a summary of the module while the bottom one presents its code."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-overview",
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
