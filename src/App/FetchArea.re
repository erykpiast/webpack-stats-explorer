open Rationale.Function;
open Rationale.Function.Infix;

exception CorsExn;
exception NotFoundExn;
exception EmptyResponseExn;
exception OtherExn(int);

module Styles = {
  open Css;

  let root = style([position(`relative)]);

  let textArea =
    style([
      fontSize(`inherit_),
      fontFamily(`inherit_),
      width(`percent(100.0)),
      boxSizing(`borderBox),
      minHeight(`percent(100.0)),
    ]);

  let submit =
    style([
      margin(px(0)),
      position(`absolute),
      top(`percent(50.0)),
      left(`percent(50.0)),
      transforms([
        `translateX(`percent(-50.0)),
        `translateY(`percent(-50.0)),
      ]),
    ]);
};

let fetch = urls =>
  Js.Promise.(
    urls
    |> Utils.String.split("\n")
    |> Array.map(Utils.String.trim)
    |> Utils.Array.filter(String.length ||> (!==)(0))
    |> Utils.Array.map(
         Fetch.(
           fetch
           ||> then_(response =>
                 switch (response |> Response.status) {
                 | 200 => response |> Response.text
                 | 204 => reject(EmptyResponseExn)
                 | 404 => reject(NotFoundExn)
                 | code => reject(OtherExn(code))
                 }
               )
           ||> catch(_ => reject(CorsExn))
         ),
       )
    |> all
  );

[@react.component]
let make = (~className="", ~onFiles) => {
  let (value, setValue) = React.useState(() => "");
  let onSubmit = fetch ||> onFiles;

  <div className={Cn.make([className, Styles.root])}>
    <textarea
      className=Styles.textArea
      onInput={e => e->ReactEvent.Form.target##value |> setValue}
    />
    {String.length(value) > 0
       ? <Button
           className=Styles.submit
           onClick={_ => onSubmit(value)}
           type_=Button.Primary>
           {L10N.Welcome.download |> React.string}
         </Button>
       : React.null}
  </div>;
};