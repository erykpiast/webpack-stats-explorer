module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"... and " |> React.string}
      <code> {"api.js" |> React.string} </code>
      {" modules." |> React.string}
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
        ~navigationPath=["app", "src", "lib", "api.js"],
        ~tab=2,
        ~splitView=true,
        ~timeline=false,
        ~index=1,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
