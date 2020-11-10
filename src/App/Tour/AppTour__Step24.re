module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"When you look closely at " |> React.string}
        <code> {"PARSED" |> React.string} </code>
        {" tab, you can find a few things missing, like " |> React.string}
        <code> {"asyncToGenerator" |> React.string} </code>
        {" functions (easy to distinguish thanks to references to global "
         |> React.string}
        <code> {"Promise" |> React.string} </code>
        {" object which name cannot be minified). Why one module needs these
      functions while another one does not?"
         |> React.string}
      </p>
      <p>
        {"The truth is a bit more complicated. Babel generates exactly the same
        code for both modules, but when Webpck bundles app into a siingle file,
        it's sometimes able to concatenate (inline) modules and get rid of
        duplicated code. In such a case only a single copy of "
         |> React.string}
        <code> {"asyncToGenerator" |> React.string} </code>
        {" remains in the final bundle." |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-code",
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
