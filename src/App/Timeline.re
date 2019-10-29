open Rationale.Function;
open Rationale.Option;

module Styles = {
  open Css;

  let root = style([]);
};

[@react.component]
let make = (~className="", ~stats=[], ~selectedIndex) => {
  let (rootWidth, setRootWidth) = React.useState(() => 0);
  let (rootElement, setRootElement) = React.useState(() => Js.Nullable.null);
  let getRootWidth =
    Js.Nullable.toOption
    ||> fmap(
          (
            (element, _) =>
              Webapi.Dom.(
                Element.getBoundingClientRect(element)
                |> DomRect.width
                |> int_of_float
              )
          )
          ||> setRootWidth,
        );
  let resizeHandler = _ => {
    getRootWidth(rootElement);
    ();
  };
  Webapi.Dom.(
    React.useEffect(
      () => {
        Window.addEventListener("resize", resizeHandler, window);

        Some(
          () => Window.removeEventListener("resize", resizeHandler, window),
        );
      },
    )
  );

  let data =
    stats
    |> Array.of_list
    |> Array.map((stat: WebpackStats.t) => {
         let entryFromChunk = Entry.FromChunk.make(stat.assets);
         let size =
           stat.chunks
           |> List.map(chunk => entryFromChunk(chunk).size)
           |> Utils.List.sumInt;
         {"timestamp": stat.builtAt, "size": size};
       });

  BsRecharts.(
    <div
      className={Cn.make([className, Styles.root])}
      ref={ReactDOMRe.Ref.callbackDomRef(element => {
        setRootElement(_ => element);
        getRootWidth(element);
        ();
      })}>
      <AreaChart data width=rootWidth height=300>
        <XAxis dataKey="timestamp" />
        <YAxis />
        <Area dataKey="size" stroke="#8884d8" fill="#8884d8" />
      </AreaChart>
    </div>
  );
};