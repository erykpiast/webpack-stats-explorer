module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"It turns out that Babel generates quite a lot of code to accurately
        transpile "
         |> React.string}
        <code> {"async" |> React.string} </code>
        {" functions to ES5. It also imports quite big " |> React.string}
        <code> {"regenerator" |> React.string} </code>
        {" module that we spotted at the start of our analysis."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-code",
    content: `element(<Content />),
    position: `top,
    action: _ => {
      setState(
        ~navigationPath=["app", "src", "app.js"],
        ~tab=1,
        ~splitView=true,
        ~timeline=false,
        ~index=0,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
