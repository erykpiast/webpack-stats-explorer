module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"There is only one module in the " |> React.string}
      <code> {"regenerator-runtime" |> React.string} </code>
      {" directory, it's " |> React.string}
      <code> {"runtime.js" |> React.string} </code>
      {". The red number without a gray one means that the module was added by the
         latest changeset - it wasn't present in the bundle before."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree-item-3",
    content: `element(<Content />),
    position: `right,
    action: _ => {
      setState(
        ~navigationPath=["app", "node_modules", "regenerator-runtime"],
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
