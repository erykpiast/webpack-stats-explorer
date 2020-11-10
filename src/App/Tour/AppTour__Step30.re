module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"Look at the " |> React.string}
      <code> {"api.js" |> React.string} </code>
      {" module for example. The definition of " |> React.string}
      <code> {"asyncToGenerator" |> React.string} </code>
      {" function is replaced with an import." |> React.string}
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
