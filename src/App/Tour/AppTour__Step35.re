module Content = {
  [@react.component]
  let make = () => React.null
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "body",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=[],
        ~tab=1,
        ~splitView=false,
        ~timeline=false,
        ~index=-1,
        (),
      );
    },
    style: ReactDOMRe.Style.make(()),
    stepInteraction: false,
    navDotAriaLabel: "",
  };
