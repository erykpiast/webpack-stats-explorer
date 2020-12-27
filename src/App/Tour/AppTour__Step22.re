module Content = {
  [@react.component]
  let make = () => {
    <p>
      {"Before the code goes to the browser it's compressed
      by Terser, which can minify variable names and erase unused code.
      Unfortunately the final size of the module is still multiplied by five,
      going from 160 bytes to more than a 1 kB."
       |> React.string}
    </p>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-code",
    content: `element(<Content />),
    position: `top,
    action: _ => {
      setState(
        ~navigationPath=["app", "src", "app.js"],
        ~tab=2,
        ~splitView=true,
        ~timeline=false,
        ~index=0,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
