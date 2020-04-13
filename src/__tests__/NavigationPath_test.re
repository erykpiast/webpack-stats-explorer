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
          fromEntries(("bar", CompareKind.Added), [foo, bar, baz]);
        let expected = Some((CompareEntry.Entry(bar), CompareKind.Added));

        expect(result) |> toEqual(expected);
      });

      test("no entry with given ID", () => {
        let result =
          fromEntries(("qux", CompareKind.Added), [foo, bar, baz]);

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
          fromCompareEntry(("bar", CompareKind.Added), comparison);
        let expected = Some((CompareEntry.Entry(bar), CompareKind.Added));

        expect(result) |> toEqual(expected);
      });

      test("there is a removed entry with given ID", () => {
        let result =
          fromCompareEntry(("baz", CompareKind.Removed), comparison);
        let expected = Some((CompareEntry.Entry(baz), CompareKind.Removed));

        expect(result) |> toEqual(expected);
      });

      test("there is an intact entry with given ID", () => {
        let result =
          fromCompareEntry(("qux", CompareKind.Intact), comparison);
        let expected = Some((CompareEntry.Entry(qux), CompareKind.Intact));

        expect(result) |> toEqual(expected);
      });

      test("there is a modified entry with given ID", () => {
        let result =
          fromCompareEntry(("bax", CompareKind.Modified), comparison);
        let expected =
          Some((CompareEntry.ModifiedEntry(bax), CompareKind.Modified));

        expect(result) |> toEqual(expected);
      });

      test("no added entry with given ID", () => {
        let result =
          fromCompareEntry(("sax", CompareKind.Added), comparison);

        expect(result) |> toEqual(None);
      });

      test("no removed entry with given ID", () => {
        let result =
          fromCompareEntry(("sax", CompareKind.Removed), comparison);

        expect(result) |> toEqual(None);
      });

      test("no intact entry with given ID", () => {
        let result =
          fromCompareEntry(("sax", CompareKind.Intact), comparison);

        expect(result) |> toEqual(None);
      });

      test("no modified entry with given ID", () => {
        let result =
          fromCompareEntry(("sax", CompareKind.Modified), comparison);

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
            ("bar", CompareKind.Added),
            ("baz", CompareKind.Added),
            ("qux", CompareKind.Added),
          ],
        );

      let expected = [
        (CompareEntry.Entry(bar), CompareKind.Added),
        (CompareEntry.Entry(baz), CompareKind.Added),
        (CompareEntry.Entry(qux), CompareKind.Added),
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
            ("bar", CompareKind.Removed),
            ("baz", CompareKind.Removed),
            ("qux", CompareKind.Removed),
          ],
        );

      let expected = [
        (CompareEntry.Entry(bar), CompareKind.Removed),
        (CompareEntry.Entry(baz), CompareKind.Removed),
        (CompareEntry.Entry(qux), CompareKind.Removed),
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
            ("bar", CompareKind.Intact),
            ("baz", CompareKind.Intact),
            ("qux", CompareKind.Intact),
          ],
        );

      let expected = [
        (CompareEntry.Entry(bar), CompareKind.Intact),
        (CompareEntry.Entry(baz), CompareKind.Intact),
        (CompareEntry.Entry(qux), CompareKind.Intact),
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
            ("foo", CompareKind.Modified),
            ("bar", CompareKind.Modified),
            ("baz", CompareKind.Added),
            ("qux", CompareKind.Added),
          ],
        );

      let expected = [
        (CompareEntry.ModifiedEntry(foo), CompareKind.Modified),
        (CompareEntry.ModifiedEntry(bar), CompareKind.Modified),
        (CompareEntry.Entry(baz), CompareKind.Added),
        (CompareEntry.Entry(qux), CompareKind.Added),
      ];

      expect(result) |> toEqual(expected);
    });
  });
});