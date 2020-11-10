module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"It turns out, that the " |> React.string}
        <code> {"regenerator-runtime" |> React.string} </code>
        {" module takes the majority of the size added to " |> React.string}
        <code> {"node_modules" |> React.string} </code>
        {". " |> React.string}
      </p>
      <p>
        <code> {"@babel" |> React.string} </code>
        {" gots bigger by just 30 bytes, so we can ignore it safely."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree-item-2",
    content: `element(<Content />),
    position: `right,
    action: _ => {
      setState(
        ~navigationPath=["app", "node_modules"],
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
