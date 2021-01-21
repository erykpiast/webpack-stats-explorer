module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"It's exactly the same for " |> React.string}
      <code> {"app.js" |> React.string} </code>
      {" module, but there is also some other utility module imported." |> React.string}
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
        ~navigationPath=["app", "src", "app.js"],
        ~tab=1,
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
