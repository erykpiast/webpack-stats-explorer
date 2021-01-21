module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"This solution is reliable and works despite having two entrypoints which is good.
      It doesn't give us as good results as automatic module sharing, though. After the optimization total
      chunk size is still bigger than before we introduced the second chunk."
         |> React.string}
      </p>
      <p>
        {"To see how chunks sizes change over time, let's look at the timeline."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#show-timeline",
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
