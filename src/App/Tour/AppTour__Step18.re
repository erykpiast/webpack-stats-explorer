module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"Let's take a look and see how the original code changed."
         |> React.string}
      </p>
      <p>
        {"All those functions that you could see in the " |> React.string}
        <code> {"Stat" |> React.string} </code>
        {" code are not present here. There is also no trace of "
         |> React.string}
        <code> {"regenerator/runtime/index.js" |> React.string} </code>
        {" module." |> React.string}
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
        ~navigationPath=["app", "src", "app.js"],
        ~tab=0,
        ~splitView=false,
        ~timeline=false,
        ~index=0,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
