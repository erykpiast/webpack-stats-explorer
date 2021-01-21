module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"Unfortunatelly it's very easy to start sending more bytes than necessary
      to the user. Changing the build configuration or upgrading dependencies
      may cause a grow difficult to explaing without digging deeply in the
      contents of minified code. It's much easier with the right tool at your
      hand."
         |> React.string}
      </p>
      <p>
        <code> {"Webpack Stats Explorer" |> React.string} </code>
        {" can help you find reasons of why your bundle size increased.
        Let's upload your own bundle statss and try it by yourself!"
         |> React.string}
      </p>
    </>;
  };
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
        ~index=0,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: false,
    navDotAriaLabel: "",
  };
