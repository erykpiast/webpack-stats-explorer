module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"There is one module marked with a yellow highlight,
      it's "
       |> React.string}
      <code> {"index.js" |> React.string} </code>
      {" inside " |> React.string}
      <code> {"regenerator" |> React.string} </code>
      {" directory. Such a highlight means, that this module imports the one
      currently selected."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree",
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
