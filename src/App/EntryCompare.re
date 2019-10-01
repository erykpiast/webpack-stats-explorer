// TODO: unify with ModulesCompare

open CompareEntry;
open State.NavigationPath;

let component = ReasonReact.statelessComponent("EntryCompare");

let putAddedFirst =
  List.sort((a: EntryDiff.props, b: EntryDiff.props) => {
    let aDiff = a.after - a.before;
    let bDiff = b.after - b.before;
    let diffOfDiffs = bDiff - aDiff;

    if (diffOfDiffs === 0) {
      0;
    } else if (aDiff === 0) {
      1;
    } else if (bDiff === 0) {
      (-1);
    } else {
      diffOfDiffs;
    };
  });

let mapChunksToProps =
  Rationale.Function.Infix.(
    (entries, onEntry) => {
      let added =
        entries.added
        |> List.map((entry: Entry.t) =>
             (
               {
                 after: entry.size,
                 before: 0,
                 name: entry.id,
                 value: Entry(entry),
                 onChange: Segment.of_entry(Added) ||> onEntry,
               }: EntryDiff.props
             )
           );
      let removed =
        entries.removed
        |> List.map((entry: Entry.t) =>
             (
               {
                 after: 0,
                 before: entry.size,
                 name: entry.id,
                 value: Entry(entry),
                 onChange: Segment.of_entry(Removed) ||> onEntry,
               }: EntryDiff.props
             )
           );
      let intact =
        entries.intact
        |> List.map((entry: Entry.t) =>
             (
               {
                 after: entry.size,
                 before: entry.size,
                 name: entry.id,
                 value: Entry(entry),
                 onChange: Segment.of_entry(Intact) ||> onEntry,
               }: EntryDiff.props
             )
           );
      let modified =
        entries.modified
        |> List.map((entry: ModifiedEntry.t(CompareEntry.t)) =>
             (
               {
                 after: entry.size |> snd,
                 before: entry.size |> fst,
                 name: entry.id,
                 value: ModifiedEntry(entry),
                 onChange: Segment.of_entry(Modified) ||> onEntry,
               }: EntryDiff.props
             )
           );

      Belt.List.concatMany([|added, modified, removed, intact|])
      |> putAddedFirst;
    }
  );

let make = (~entries, ~onEntry, ~selected, ~className="", _children) => {
  ...component,
  render: _self =>
    <EntryDiff
      data={mapChunksToProps(entries, onEntry)}
      selected
      className
    />,
};