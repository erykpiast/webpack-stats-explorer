module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"Code of this module doesn't say us much. It's just an import
        of "
         |> React.string}
        <code> {"regenerator-runtime" |> React.string} </code>
        {". that we've seem a while ago." |> React.string}
      </p>
      <p>
        {"The fact that the module is placed under the " |> React.string}
        <code> {"@babel" |> React.string} </code>
        {". namespace suggests to us, that it has something to do with code
        transpilation."
         |> React.string}
      </p>
      <p>
        {"Let's go back to the sidebar to look for the reason of "
         |> React.string}
        <code> {"regenerator/index.js" |> React.string} </code>
        {" module." |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-overview",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=[
          "app",
          "node_modules",
          "@babel",
          "runtime",
          "regenerator",
          "index.js",
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
