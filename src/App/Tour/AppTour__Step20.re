module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"What you can see now is that a regular function with "
         |> React.string}
        <code> {"then" |> React.string} </code>
        {" callbacks was replaced by an approach using the new "
         |> React.string}
        <code> {"async/await" |> React.string} </code>
        {" syntax." |> React.string}
      </p>
      <p>
        {"The source code is more succint now. Objectively speaking, it's
        five characters less than before."
         |> React.string}
      </p>
      <p>
        {"It doesn't look so good when it comes to the generated code. Let's
        see inside the "
         |> React.string}
        <code> {"STAT" |> React.string} </code>
        {" tab." |> React.string}
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
