open Rationale.Function.Infix;

let component = ReasonReact.statelessComponent("WelcomeScreen");

module Styles = {
  open Css;

  let dropzone = style([height(`percent(100.0))]);

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
      width(`percent(100.0)),
      justifyContent(`center),
      textAlign(`center),
    ]);

  let action =
    style([
      fontSize(em(1.5)),
      padding2(~v=Theme.Space.double, ~h=Theme.Space.quadruple),
    ]);

  let paste =
    style([
      fontSize(Theme.Size.Text.default),
      fontFamily(`monospace),
      minHeight(em(5.0)),
      width(`percent(80.0)),
      margin2(~v=px(0), ~h=`auto),
      maxWidth(Theme.Space.quadruplehexteenfold),
    ]);
};

let logStats = (title, stats) => {
  Js.log(title);
  stats |> WebpackStats.encode |> Js.log;
};

let logComp = (title, comp) => {
  Js.log(title);
  comp |> CompareEntry.encode |> Js.log;
};

let loadExampleData = _ => [Data.a, Data.b, Data.c, Data.d, Data.e];

type failReason =
  | NotEnoughFiles
  | WrongFormat
  | ParsingFailed
  | UnsupportedVersion
  | EmptyResponse
  | CorsIssue
  | FileNotFound
  | OtherFetchingError(int);

type status =
  | Success
  | Fail(failReason)
  | Unknown;

type state = {
  status,
  resetParsingStatusTimeout: option(Js.Global.timeoutId),
};

exception NotEnoughFilesExn;

let getLabel = status =>
  switch (status) {
  | Success => Some(L10N.Validation.success)
  | Fail(reason) =>
    switch (reason) {
    | NotEnoughFiles => Some(L10N.Validation.notEnough)
    | WrongFormat => Some(L10N.Validation.json)
    | ParsingFailed => Some(L10N.Validation.stats)
    | UnsupportedVersion => Some(L10N.Validation.version)
    | EmptyResponse => Some(L10N.Fetch.empty)
    | CorsIssue => Some(L10N.Fetch.cors)
    | FileNotFound => Some(L10N.Fetch.notFound)
    | OtherFetchingError(code) =>
      Some(L10N.Fetch.unknown ++ " " ++ string_of_int(code))
    }
  | Unknown => None
  };

[@react.component]
let make = (~urls, ~onStats, ~onUrls, ~children) => {
  let (status, setStatus) = React.useState(() => Unknown);
  React.useEffect1(
    () => {
      let timeout = Js.Global.setTimeout(() => setStatus(_ => Unknown), 5000);
      Some(() => Js.Global.clearTimeout(timeout));
    },
    [|status|],
  );
  let (filesPromise, setFilesPromise) = React.useState(() => None);
  let failureHandler =
    [@bs.open]
    (
      fun
      | WebpackStats.FromText.UnsupportedVersionExn => UnsupportedVersion
      | WebpackStats.FromText.ParsingFailedExn => ParsingFailed
      | FetchArea.CorsExn => CorsIssue
      | FetchArea.NotFoundExn => FileNotFound
      | FetchArea.EmptyResponseExn => EmptyResponse
      | FetchArea.OtherExn(code) => OtherFetchingError(code)
      | NotEnoughFilesExn => NotEnoughFiles
    )
    ||> Utils.defaultTo(ParsingFailed);
  React.useEffect1(
    () =>
      switch (filesPromise) {
      | Some(promise) =>
        let unmounted = ref(false);
        Js.Promise.(
          promise
          |> then_(Array.map(WebpackStats.FromText.make) ||> all)
          |> then_(stats =>
              switch (Array.length(stats)) {
              | 0 => reject(NotEnoughFilesExn)
              | 1 => resolve(Array.concat([stats, stats]))
              | _ => resolve(stats)
              }
             )
          |> then_(Array.to_list ||> onStats ||> (_ => Success |> resolve))
          |> catch(failureHandler ||> (err => Fail(err) |> resolve))
          |> then_(status => {
               if (! unmounted^) {
                 setStatus(_ => status);
               };

               resolve();
             })
          |> ignore
        );

        Some(() => unmounted := true);
      | None => None
      },
    [|filesPromise|],
  );

  let label = status |> getLabel;
  let onFiles = filesPromise => setFilesPromise(_ => Some(filesPromise));

  <Dropzone className=Styles.dropzone onFiles label>
    {onClick =>
       children(
         <div className=Styles.wrapper>
           <p> {L10N.Welcome.paste |> React.string} </p>
           <div>
             <FetchArea className=Styles.paste urls onFiles onUrls />
           </div>
           <p>
             {L10N.Welcome.or_ ++ " " ++ L10N.Welcome.drag |> React.string}
           </p>
           <div>
             <Button onClick type_=Button.Primary className=Styles.action>
               {L10N.Welcome.upload |> React.string}
             </Button>
           </div>
           <p> {L10N.Welcome.or_ |> React.string} </p>
           <div>
             <Button
               onClick={loadExampleData ||> onStats ||> ignore}
               className=Styles.action>
               {L10N.Welcome.loadExample |> React.string}
             </Button>
           </div>
         </div>,
       )}
  </Dropzone>;
};