module Content = {
  [@react.component]
  let make = () => {
    <p> {"This is the one! Let's take a look inside it." |> React.string} </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree-item-7",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=[
          "app",
          "node_modules",
          "regenerator-runtime",
          "runtime.js",
        ],
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
