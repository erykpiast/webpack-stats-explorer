open Rationale.Function.Infix;
module Styles = {
  open Css;

  let dropzone = style([height(`percent(100.0))]);
};

let logStats = (title, stats) => {
  Js.log(title);
  stats |> WebpackStats.encode |> Js.log;
};

let logComp = (title, comp) => {
  Js.log(title);
  comp |> CompareEntry.encode |> Js.log;
};

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
let make = (~onStats, ~initial, ~children) => {
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
               switch (stats) {
               | [||] => reject(NotEnoughFilesExn)
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
    {onClick => children(onClick, onFiles)}
  </Dropzone>;
};