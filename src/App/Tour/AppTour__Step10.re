module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"There is also the third tab, " |> React.string}
      <code> {"Original" |> React.string} </code>
      {", which contains original source code - the one you see in the IDE,
          when you're authoring the program."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-size-original",
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
        ~tab=0,
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
