module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"A lot is happenning here! In the very first line we can see
         an import of "
         |> React.string}
        <code> {"@babel/runtime/regenerator" |> React.string} </code>
        {" package. It is the " |> React.string}
        <code> {"index.js" |> React.string} </code>
        {" module that we were looking at just a while before." |> React.string}
        {"The higlight color for this line is green, what means it wasn't present
        before and was just added - it's regular diff after all."
         |> React.string}
      </p>
      <p>
        {"There is actually quite much code added to the module. It looks like
        it's all about dealing with asynchronicity."
         |> React.string}
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
        ~navigationPath=["app", "src", "app.js"],
        ~tab=1,
        ~splitView=false,
        ~timeline=false,
        ~index=0,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
