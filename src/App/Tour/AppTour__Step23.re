module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"You can see that similar code was added to " |> React.string}
      <code> {"api.js" |> React.string} </code>
      {" module, which grows significantly as well. You can easily spot "
       |> React.string}
      <code> {"switch" |> React.string} </code>
      {" statements that look almost exactly the same as in the " |> React.string}
      <code> {"app.js" |> React.string} </code>
      {" module." |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-code",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=["app", "src", "lib", "api.js"],
        ~tab=1,
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
