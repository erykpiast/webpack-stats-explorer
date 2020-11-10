module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"You can see that the code wich was previously de-duplicated and present only in the "
       |> React.string}
      <code> {"app.js" |> React.string} </code>
      {" file, is now placed in both " |> React.string}
      <code> {"utils.js" |> React.string} </code>
      {" and..." |> React.string}
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
        ~navigationPath=["app", "src", "lib", "utils.js"],
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
