module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"There are four kind of entires, each with a different color assigned
            to it:"
         |> React.string}
      </p>
      <ul>
        <li>
          <code
            className=Css.(
              style([fontWeight(`bold), color(Theme.Color.Added.default)])
            )>
            {"added" |> React.string}
          </code>
          {" the module wasn't present before in the bundle. You can see this one
              here"
           |> React.string}
        </li>
        <li>
          <code
            className=Css.(
              style([fontWeight(`bold), color(Theme.Color.Removed.default)])
            )>
            {"removed" |> React.string}
          </code>
          {" the module was present in the bundle till now, but it's
              not anymore."
           |> React.string}
        </li>
        <li>
          <code
            className=Css.(
              style([
                fontWeight(`bold),
                color(Theme.Color.Modified.default),
              ])
            )>
            {"modified" |> React.string}
          </code>
          {" the module was present in the bundle before and was altered
              in some way. It may mean that some new code appeared but also that
              the module size was reduced."
           |> React.string}
        </li>
        <li>
          <code
            className=Css.(
              style([fontWeight(`bold), color(Theme.Color.Intact.default)])
            )>
            {"intact" |> React.string}
          </code>
          {" the module was present in the bundle before and it is still in the
              unchanged form"
           |> React.string}
        </li>
      </ul>
      <p>
        {"You can think of the kind as of a file status in Git. "
         |> React.string}
        {"That's what Webpack Stats Explorer is - " |> React.string}
        <strong>
          {"it's a version control for your bundles." |> React.string}
        </strong>
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-kind",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=[
          "app",
          "node_modules",
          "regenerator-runtime",
          "runtime.js",
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
