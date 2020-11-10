module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"You can clearly see how the size of the " |> React.string}
      <code> {"app" |> React.string} </code>
      {" chunk increased after the " |> React.string}
      <code> {"async" |> React.string} </code>
      {"/" |> React.string}
      <code> {"await" |> React.string} </code>
      {" syntax was introduced. Then, after adding the " |> React.string}
      <code> {"lib" |> React.string} </code>
      {" entrypoint. Finally, how it decreased when we enabled shared helpers."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#timeline",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=["app", "src", "app.js"],
        ~tab=1,
        ~splitView=true,
        ~timeline=true,
        ~index=2,
        (),
      );
    },
    style: ReactDOMRe.Style.make(()),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
