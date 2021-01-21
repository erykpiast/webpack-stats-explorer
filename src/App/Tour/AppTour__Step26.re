module Content = {
  [@react.component]
  let make = () => {
    <>
      <p>
        {"It's enough to add the second entrypoint to confuse Webpack and
        introduce code duplication. See all these bytes added to modules in the "
         |> React.string}
        <code> {"lib" |> React.string} </code>
        {" directory of the " |> React.string}
        <code> {"app" |> React.string} </code>
        {" chunk. The size of the " |> React.string}
        <code> {"app.js" |> React.string} </code>
        {" file itself decreased, but in total the whole chunk grew significantly."
         |> React.string}
      </p>
      <p>
        {"It happened despite we didn't touch the source code of the app itself. Only
        some distant and, at the first sight, unrelated parts of codebase were modified.
        That's a very fragile setup."
         |> React.string}
      </p>
    </>;
  };
};

let getStep = (setState: UrlState.Make.t) =>
  Reactour.Steps.Step.{
    selector: "#entry-tree",
    content: `element(<Content />),
    position: `left,
    action: _ => {
      setState(
        ~navigationPath=["app", "src", "lib"],
        ~tab=1,
        ~splitView=false,
        ~timeline=false,
        ~index=1,
        (),
      );
    },
    style: ReactDOMRe.Style.make(),
    stepInteraction: true,
    navDotAriaLabel: "",
  };
