open Jest;
open ExpectJs;

describe("EntryCompare", () =>
  describe("putAddedFirst", () => {
    let mockEntry = (before, after) =>
      EntryDiff.EntryDiff.{
        after,
        before,
        name: "",
        value:
          Entry(
            Entry.{
              id: "foo",
              size: 0,
              children: [],
              stat: None,
              original: None,
              parsed: None,
            },
          ),
        onChange: _ => (),
      };

    test("it should put added modules first and intact last", () => {
      let added = mockEntry(0, 100);
      let intact = mockEntry(200, 200);
      let removed = mockEntry(50, 0);

      let sorted = EntryCompare.putAddedFirst([intact, removed, added]);

      expect(sorted) |> toEqual([added, removed, intact]);
    });

    test(
      "it should put modified modules with more code added above added ones",
      () => {
      let added = mockEntry(0, 100);
      let modified1 = mockEntry(200, 250);
      let modified2 = mockEntry(200, 400);

      let sorted = EntryCompare.putAddedFirst([added, modified1, modified2]);

      expect(sorted) |> toEqual([modified2, added, modified1]);
    });
  })
);