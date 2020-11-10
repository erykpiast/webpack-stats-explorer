module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"Let's start from selecting the chunk and display all modules inside
        it. "
         |> React.string}
      </p>
      <p>
        {"In this example you can see only one chunk, but in more complex
          applications with code splitting there will be much more of them.
          Each with its own modules."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree-item-0",
    content: `element(<Content />),
    position: `right,
    action: _ => {
      setState(
        ~navigationPath=[],
        ~tab=1,
        ~sourceTree=false,
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
