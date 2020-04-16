open Jest;
open ExpectJs;

describe("NavigationPath", () => {
  open NavigationPath;

  let makeEntry = (~children=[], id) =>
    Entry.{id, size: 666, children, original: None, stat: None, parsed: None};
  let makeModifiedEntry = (~children=CompareEntry.empty, id) =>
    ModifiedEntry.{
      id,
      size: (333, 666),
      children,
      original: None,
      stat: None,
      parsed: None,
    };

  describe("Segment", () => {
    open Segment;

    let foo = makeEntry("foo");
    let bar = makeEntry("bar");
    let baz = makeEntry("baz");
    let qux = makeEntry("qux");
    let fux = makeModifiedEntry("fux");
    let bax = makeModifiedEntry("bax");

    describe("from entries", () => {
      test("there is an entry with given ID", () => {
        let result =
          fromEntries("bar", [foo, bar, baz]);
        let expected = Some(CompareEntry.Entry(bar));

        expect(result) |> toEqual(expected);
      });

      test("no entry with given ID", () => {
        let result =
          fromEntries("qux", [foo, bar, baz]);

        expect(result) |> toEqual(None);
      });
    });

    describe("from compare entry", () => {
      let comparison =
        CompareEntry.{
          added: [foo, bar],
          removed: [foo, baz],
          intact: [foo, qux],
          modified: [fux, bax],
        };

      test("there is an added entry with given ID", () => {
        let result =
          fromCompareEntry("bar", comparison);
        let expected = Some(CompareEntry.Entry(bar));

        expect(result) |> toEqual(expected);
      });

      test("there is a removed entry with given ID", () => {
        let result =
          fromCompareEntry("baz", comparison);
        let expected = Some(CompareEntry.Entry(baz));

        expect(result) |> toEqual(expected);
      });

      test("there is an intact entry with given ID", () => {
        let result =
          fromCompareEntry("qux", comparison);
        let expected = Some(CompareEntry.Entry(qux));

        expect(result) |> toEqual(expected);
      });

      test("there is a modified entry with given ID", () => {
        let result =
          fromCompareEntry("bax", comparison);
        let expected =
          Some(CompareEntry.ModifiedEntry(bax));

        expect(result) |> toEqual(expected);
      });

      test("no entry with given ID", () => {
        let result =
          fromCompareEntry("sax", comparison);

        expect(result) |> toEqual(None);
      });
    });
  });

  describe("from state", () => {
    let qux = makeEntry("qux");
    let baz = makeEntry(~children=[makeEntry("bax"), qux], "baz");
    let bar = makeEntry(~children=[baz, makeEntry("fux")], "bar");

    test("added", () => {
      let comparison =
        CompareEntry.{
          added: [makeEntry("foo"), bar],
          removed: [],
          intact: [],
          modified: [],
        };

      let result =
        fromState(
          CompareEntry.ModifiedChildren(comparison),
          [
            "bar",
            "baz",
            "qux",
          ],
        );

      let expected = [
        CompareEntry.Entry(bar),
        CompareEntry.Entry(baz),
        CompareEntry.Entry(qux),
      ];

      expect(result) |> toEqual(expected);
    });

    test("removed", () => {
      let comparison =
        CompareEntry.{
          added: [],
          removed: [makeEntry("foo"), bar],
          intact: [],
          modified: [],
        };

      let result =
        fromState(
          CompareEntry.ModifiedChildren(comparison),
          [
            "bar",
            "baz",
            "qux",
          ],
        );

      let expected = [
        CompareEntry.Entry(bar),
        CompareEntry.Entry(baz),
        CompareEntry.Entry(qux),
      ];

      expect(result) |> toEqual(expected);
    });

    test("intact", () => {
      let comparison =
        CompareEntry.{
          added: [],
          removed: [],
          intact: [makeEntry("foo"), bar],
          modified: [],
        };

      let result =
        fromState(
          CompareEntry.ModifiedChildren(comparison),
          [
            "bar",
            "baz",
            "qux",
          ],
        );

      let expected = [
        CompareEntry.Entry(bar),
        CompareEntry.Entry(baz),
        CompareEntry.Entry(qux),
      ];

      expect(result) |> toEqual(expected);
    });

    test("modified", () => {
      let qux = makeEntry("qux");
      let baz = makeEntry(~children=[makeEntry("bax"), qux], "baz");
      let bar =
        makeModifiedEntry(
          ~children=
            CompareEntry.{
              added: [baz, makeEntry("fux")],
              removed: [makeEntry("hux")],
              intact: [],
              modified: [makeModifiedEntry("fax")],
            },
          "bar",
        );
      let foo =
        makeModifiedEntry(
          ~children=
            CompareEntry.{
              added: [makeEntry("qur")],
              removed: [],
              intact: [makeEntry("bux")],
              modified: [makeModifiedEntry("qax"), bar],
            },
          "foo",
        );

      let comparison =
        CompareEntry.{added: [], removed: [], intact: [], modified: [foo]};

      let result =
        fromState(
          CompareEntry.ModifiedChildren(comparison),
          [
            "foo",
            "bar",
            "baz",
            "qux",
          ],
        );

      let expected = [
        CompareEntry.ModifiedEntry(foo),
        CompareEntry.ModifiedEntry(bar),
        CompareEntry.Entry(baz),
        CompareEntry.Entry(qux),
      ];

      expect(result) |> toEqual(expected);
    });
  });
});