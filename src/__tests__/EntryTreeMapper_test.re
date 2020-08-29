open Jest;
open ExpectJs;

describe("EntryTreeMapper.Mapper", () => {
  describe("sortProps", () => {
    module Mapper =
      EntryTreeMapper.Mapper({
        let onEntry = (_, _) => ();
        let onPath = _ => ();
        let navigationPath = [];
        let reasons = [];
      });

    let entry =
      CompareEntry.Entry(
        Entry.{
          id: "foo",
          size: 0,
          children: [],
          stat: None,
          original: None,
          parsed: None,
          reasons: [],
        },
      );
    let mockEntry =
        (~level=0, ~parent=None, ~name="", ~value=entry, before, after) =>
      Mapper.{
        state: `collapsed,
        value: {
          after,
          before,
          name,
          value,
          parent,
          level,
          onCollapse: _ => (),
          onExpand: _ => (),
          onSelect: (_, _) => (),
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

  Only.describe("mapToProps", () => {
    let mockEntry = (children, id) =>
      Entry.{
        id,
        size: 100,
        children,
        stat: None,
        original: None,
        parsed: None,
        reasons: [],
      };
    let d1 = mockEntry([], "d1");
    let c3 = mockEntry([], "c3");
    let c2 = mockEntry([d1], "c2");
    let c1 = mockEntry([], "c1");
    let b2 = mockEntry([c1, c2, c3], "b2");
    let b1 = mockEntry([], "b1");
    let a1 = mockEntry([b1, b2], "a1");
    let reason1 = CompareEntry.[Entry(a1), Entry(b1)];
    let reason2 = CompareEntry.[Entry(a1), Entry(b2), Entry(c3)];

    test("it should expand navigationPath", () => {
      module Mapper =
        EntryTreeMapper.Mapper({
          let onEntry = (_, _) => ();
          let onPath = _ => ();
          let navigationPath =
            CompareEntry.[Entry(a1), Entry(b2), Entry(c2)];
          let reasons = [];
        });

      let mockMappedEntry =
          (
            ~state=`collapsed,
            ~level=0,
            onCollapse,
            name,
            value,
            parent,
            children,
          ) =>
        Mapper.{
          state,
          value: {
            after: 100,
            before: 0,
            name,
            value,
            parent,
            level,
            onCollapse,
            onExpand: _ => (),
            onSelect: (_, _) => (),
          },
          children,
        };

      let mapped = Mapper.added([a1]) |> List.hd;

      let rootFold = mapped.value.onCollapse;
      let childFold = List.hd(mapped.children).value.onCollapse;

      let expected =
        CompareEntry.(
          mockMappedEntry(
            ~state=`expanded,
            ~level=0,
            rootFold,
            "a1",
            Entry(a1),
            None,
            [
              mockMappedEntry(
                ~state=`collapsed,
                ~level=1,
                childFold,
                "b1",
                Entry(b1),
                Some(Entry(a1)),
                [],
              ),
              mockMappedEntry(
                ~state=`expanded,
                ~level=1,
                childFold,
                "b2",
                Entry(b2),
                Some(Entry(a1)),
                [
                  mockMappedEntry(
                    ~state=`collapsed,
                    ~level=2,
                    childFold,
                    "c1",
                    Entry(c1),
                    Some(Entry(b2)),
                    [],
                  ),
                  mockMappedEntry(
                    ~state=`selected,
                    ~level=2,
                    childFold,
                    "c2",
                    Entry(c2),
                    Some(Entry(b2)),
                    [
                      mockMappedEntry(
                        ~state=`collapsed,
                        ~level=3,
                        childFold,
                        "d1",
                        Entry(d1),
                        Some(Entry(c2)),
                        [],
                      ),
                    ],
                  ),
                  mockMappedEntry(
                    ~state=`collapsed,
                    ~level=2,
                    childFold,
                    "c3",
                    Entry(c3),
                    Some(Entry(b2)),
                    [],
                  ),
                ],
              ),
            ],
          )
        );

      expect(Utils.stringify(mapped)) |> toBe(Utils.stringify(expected));
    });

    test("it should expand reasons", () => {
      module Mapper =
        EntryTreeMapper.Mapper({
          let onEntry = (_, _) => ();
          let onPath = _ => ();
          let navigationPath =
            CompareEntry.[Entry(a1), Entry(b2), Entry(c2)];
          let reasons = [reason1, reason2];
        });

      let mockMappedEntry =
          (
            ~state=`collapsed,
            ~level=0,
            onCollapse,
            name,
            value,
            parent,
            children,
          ) =>
        Mapper.{
          state,
          value: {
            after: 100,
            before: 0,
            name,
            value,
            parent,
            level,
            onCollapse,
            onExpand: _ => (),
            onSelect: (_, _) => (),
          },
          children,
        };

      let mapped = Mapper.added([a1]) |> List.hd;

      let rootFold = mapped.value.onCollapse;
      let childFold = List.hd(mapped.children).value.onCollapse;

      let expected =
        CompareEntry.(
          mockMappedEntry(
            ~state=`expanded,
            ~level=0,
            rootFold,
            "a1",
            Entry(a1),
            None,
            [
              mockMappedEntry(
                ~state=`reason(reason1),
                ~level=1,
                childFold,
                "b1",
                Entry(b1),
                Some(Entry(a1)),
                [],
              ),
              mockMappedEntry(
                ~state=`expanded,
                ~level=1,
                childFold,
                "b2",
                Entry(b2),
                Some(Entry(a1)),
                [
                  mockMappedEntry(
                    ~state=`collapsed,
                    ~level=2,
                    childFold,
                    "c1",
                    Entry(c1),
                    Some(Entry(b2)),
                    [],
                  ),
                  mockMappedEntry(
                    ~state=`selected,
                    ~level=2,
                    childFold,
                    "c2",
                    Entry(c2),
                    Some(Entry(b2)),
                    [
                      mockMappedEntry(
                        ~state=`collapsed,
                        ~level=3,
                        childFold,
                        "d1",
                        Entry(d1),
                        Some(Entry(c2)),
                        [],
                      ),
                    ],
                  ),
                  mockMappedEntry(
                    ~state=`reason(reason2),
                    ~level=2,
                    childFold,
                    "c3",
                    Entry(c3),
                    Some(Entry(b2)),
                    [],
                  ),
                ],
              ),
            ],
          )
        );

      expect(Utils.stringify(mapped)) |> toBe(Utils.stringify(expected));
    });
  });
});
