module Styles = {
  open Css;

  let code =
    style([
      padding(Theme.Space.default),
      whiteSpace(`preWrap),
      wordBreak(`breakAll),
    ]);
};

module EntrySummary =
  GenericSummary.Make({
    open CompareEntry;
    open Rationale.Option.Infix;

    type a = entry;

    let componentName = "EntrySummary";
    let getName = entry =>
      switch (entry) {
      | Entry(entry) => entry.id
      | ModifiedEntry(entry) => entry.id
      };
    let getStatSize = entry =>
      switch (entry) {
      | Entry(entry) => switch (entry.stat) {
        | Some({ size }) => size
        | None => 0
        }
      | ModifiedEntry(entry) => switch (entry.stat) {
        | Some({ size }) => size |> snd
        | None => 0
        }
      };
    let getSize = getStatSize;
    let getOriginalSize = entry =>
      switch (entry) {
      | Entry(entry) => switch (entry.original) {
        | Some({ size }) => size
        | None => 0
        }
      | ModifiedEntry(entry) => switch (entry.original) {
        | Some({ size }) => size |> snd
        | None => 0
        }
      };
    let getParsedSize = entry =>
      switch (entry) {
      | Entry(entry) => switch (entry.parsed) {
        | Some({ size }) => size
        | None => 0
        }
      | ModifiedEntry(entry) => switch (entry.parsed) {
        | Some({ size }) => size |> snd
        | None => 0
        }
      };
    let getStatSource = entry =>
      switch (entry) {
      | Entry(entry) => switch (entry.stat) {
        | Some({ source }) => source
        | None => ""
        }
        |> (
          code =>
            <pre className=Styles.code> {code |> ReasonReact.string} </pre>
        )
      | ModifiedEntry(entry) => switch (entry.stat) {
        | Some({ source }) => <CodeDiff
            className=Styles.code
            before={source |> fst}
            after={source |> snd}
          />
        | None => ReasonReact.null
        }
      };
    let getOriginalSource = _ => None;
    let getParsedSource = _ => None;
    let getSource = getStatSource;
    
    let getModules = entry =>
      switch (entry) {
      | Entry(entry) => Some(NotModifiedChildren(entry.children))
      | ModifiedEntry(entry) => Some(ModifiedChildren(entry.children))
      };
  });

let make = EntrySummary.make;