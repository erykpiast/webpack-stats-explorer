module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"Notice how sizes differ from each other. " |> React.string}
        <code> {"Stat" |> React.string} </code>
        {" is significantly greater than the " |> React.string}
        <code> {"Original" |> React.string} </code>
        {"." |> React.string}
      </p>
      <p>
        {"Actually, we can see that the amount of " |> React.string}
        <code> {"Stat" |> React.string} </code>
        {" and " |> React.string}
        <code> {"Parsed" |> React.string} </code>
        {" code increased, while " |> React.string}
        <code> {"Original" |> React.string} </code>
        {" shrank a little bit." |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-sizes",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=["app", "src", "app.js"],
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
