open CompareEntry;

module EntryDiff =
  GenericDiff.Make({
    type a = entry;

    let componentName = "EntryDiff";
    let getName = entry =>
      switch (entry) {
      | Entry(entry) => entry.id
      | ModifiedEntry(entry) => entry.id
      };
  });

let make = EntryDiff.make;
type props = EntryDiff.props;
