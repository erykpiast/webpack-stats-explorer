module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"Do an overview of directories inside the chunk " |> React.string}
      <code> {"main" |> React.string} </code>
      {". It looks like a couple of additional kilobytes appeared in "
       |> React.string}
      <code> {"node_modules" |> React.string} </code>
      {"!" |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree",
    content: `element(<Content />),
    position: `right,
    action: _ => {
      setState(
        ~navigationPath=["app"],
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
