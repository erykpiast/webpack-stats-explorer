open CompareEntry;
open CompareKind;
open State.NavigationPath;

let mapModulesToProps = (entries, kind, onEntry) => {
  entries
  |> List.map((entry: Entry.t) => {
       let size = entry.size;
       let (after, before) =
         switch (kind) {
         | Added => (size, 0)
         | Removed => (0, size)
         | Intact => (size, size)
         | Modified => (0, 0)
         };

       (
         {
           after,
           before,
           name: entry.id,
           value: Entry(entry),
           onChange: entry => {
             onEntry(Segment.make(kind, entry));
             ();
           },
         }: EntryDiff.props
       );
     });
};

let component = ReasonReact.statelessComponent("EntryLiast");

let make = (~entries, ~onEntry, ~kind, ~selected, ~className="", _children) => {
  ...component,
  render: _self =>
    <EntryDiff
      className
      data={mapModulesToProps(entries, kind, onEntry)}
      selected
    />,
};