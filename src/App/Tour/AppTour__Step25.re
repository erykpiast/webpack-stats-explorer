module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"This optimization doesn't work for each application. For bigger
        codebases with more complex dependency tree, modules won't be inlined.
        In fact, it's better not to rely on Webpack here as rules to keep the
        bundle optimized are very easy to break. One additional "
         |> React.string}
        <code> {"import" |> React.string} </code>
        {" statement may cause unnecessary code duplication." |> React.string}
      </p>
      <p>
        {"Let's switch to the next comparision and see an example of such an
        accidentally deoptimised code."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#next-comparison",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=["app", "src", "lib", "api.js"],
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
