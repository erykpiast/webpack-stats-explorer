open Jest;
open ExpectJs;

describe("EntryTree.Mapper", () => {
  module Mapper =
    EntryTree.Mapper({
      let onEntry = (_, _) => ();
      let navigationPath = [];
    });

  describe("sortProps", () => {
    let entry =
      CompareEntry.Entry(
        Entry.{
          id: "foo",
          size: 0,
          children: [],
          stat: None,
          original: None,
          parsed: None,
        },
      );
    let mockEntry =
        (~level=0, ~parent=None, ~name="", ~value=entry, before, after) =>
      Mapper.{
        selected: false,
        value: {
          after,
          before,
          name,
          value,
          parent,
          level,
          onFold: _ => (),
          onUnfold: _ => (),
        },
        children: [],
      };

    test("it should put added modules first and intact last", () => {
      let added = mockEntry(0, 100);
      let intact = mockEntry(200, 200);
      let removed = mockEntry(50, 0);

      let sorted = Mapper.sortProps([intact, removed, added]);

      expect(sorted) |> toEqual([added, removed, intact]);
    });

    test(
      "it should put modified modules with more code added above added ones",
      () => {
      let added = mockEntry(0, 100);
      let modified1 = mockEntry(200, 250);
      let modified2 = mockEntry(200, 400);

      let sorted = Mapper.sortProps([added, modified1, modified2]);

      expect(sorted) |> toEqual([modified2, added, modified1]);
    });
  });
});
