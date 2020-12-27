module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"Let's go back to the default tab, " |> React.string}
        <code> {"Stat" |> React.string} </code>
        {"." |> React.string}
      </p>
      <p>
        {"The contents of " |> React.string}
        <code> {"runtime.js" |> React.string} </code>
        {" module looks unfamiliar. It's written by Facebook and doesn't bring to
        mind anything that could be explicitly imported."
         |> React.string}
      </p>
      <p>
        {"Where the module comes from? Let's go back to the sidebar
        and search there for possible reasons."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-code",
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
