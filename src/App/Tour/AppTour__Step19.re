module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"To better understand what changed, you can use the " |> React.string}
        <code> {"Split" |> React.string} </code>
        {" view." |> React.string}
      </p>
      <p>
        {"It's available only for " |> React.string}
        <code
          className=Css.(
            style([fontWeight(`bold), color(Theme.Color.Modified.default)])
          )>
          {"modified" |> React.string}
        </code>
        {" kind of modules, as only these can contain changed code."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#diff-mode",
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
    stepInteraction: false,
    navDotAriaLabel: "",
  };
