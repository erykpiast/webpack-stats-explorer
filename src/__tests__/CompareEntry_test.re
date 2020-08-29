open Jest;
open ExpectJs;

describe("CompareEntry", () => {
  let makeModified = ModifiedEntry.make((_, _) => CompareEntry.make([], []));
  let makeEntry = (~children=[], ~size=123, ~code="", id) =>
    Entry.{
      id,
      size,
      children,
      original: None,
      stat: Entry.Data.make(Some(code), Some(size)),
      parsed: None,
      reasons: [],
    };

  let foo1 = makeEntry(~code="I am foo", ~size=666, "foo");
  let foo2 = makeEntry(~code="I am different foo", ~size=555, "foo");
  let bar1 = makeEntry(~code="I am Boo", ~size=555, "bar");

  test("added", () => {
    let a = [];
    let b = [foo1, bar1];

    let comp = CompareEntry.make(a, b);

    expect(comp)
    |> toEqual(
         CompareEntry.{
           added: [foo1, bar1],
           removed: [],
           intact: [],
           modified: [],
         },
       );
  });

  test("removed", () => {
    let a = [foo1, bar1];
    let b = [];

    let comp = CompareEntry.make(a, b);

    expect(comp)
    |> toEqual(
         CompareEntry.{
           added: [],
           removed: [foo1, bar1],
           intact: [],
           modified: [],
         },
       );
  });

  test("intact", () => {
    let a = [foo1, bar1];
    let b = [foo1, bar1];

    let comp = CompareEntry.make(a, b);

    expect(comp)
    |> toEqual(
         CompareEntry.{
           added: [],
           removed: [],
           intact: [foo1, bar1],
           modified: [],
         },
       );
  });

  test("modified", () => {
    let a = [foo1];
    let b = [foo2];

    let comp = CompareEntry.make(a, b);

    expect(comp)
    |> toEqual(
         CompareEntry.{
           added: [],
           removed: [],
           intact: [],
           modified: [makeModified(foo1, foo2)],
         },
       );
  });

  describe("kind", () => {
    let foo3 = makeEntry(~children=[bar1], "foo");
    let bar2 =
      ModifiedEntry.{
        id: "bar2",
        size: (123, 321),
        children:
          CompareEntry.{
            added: [foo2],
            removed: [foo3],
            modified: [],
            intact: [bar1],
          },
        reasons: ([], []),
        original: None,
        stat:
          ModifiedEntry.Data.make(
            Entry.Data.make(Some("I am another bar"), Some(123)),
            Entry.Data.make(
              Some("I am another version of another bar"),
              Some(321),
            ),
          ),
        parsed: None,
      };

    test("top level", () => {
      let comp =
        CompareEntry.{
          added: [foo2, bar1],
          removed: [foo1],
          modified: [],
          intact: [],
        };

      let kind = CompareEntry.kind(comp, Entry(foo2), []);

      expect(kind) |> toEqual(CompareKind.Added);
    });

    test("nested not modified", () => {
      let comp =
        CompareEntry.{
          added: [foo2],
          removed: [foo3],
          modified: [],
          intact: [],
        };

      let kind = CompareEntry.kind(comp, Entry(bar1), [Entry(foo3)]);

      expect(kind) |> toEqual(CompareKind.Removed);
    });

    test("nested modified", () => {
      let comp =
        CompareEntry.{
          added: [],
          removed: [foo1],
          modified: [bar2],
          intact: [],
        };

      let kind =
        CompareEntry.kind(comp, Entry(foo2), [ModifiedEntry(bar2)]);

      expect(kind) |> toEqual(CompareKind.Added);
    });

    test("not modified nested in modified", () => {
      let comp =
        CompareEntry.{
          added: [],
          removed: [foo1],
          modified: [bar2],
          intact: [],
        };

      let kind =
        CompareEntry.kind(
          comp,
          Entry(foo2),
          [Entry(foo3), ModifiedEntry(bar2)],
        );

      expect(kind) |> toEqual(CompareKind.Removed);
    });

    test("double nested modified", () => {
      let bar3 =
        ModifiedEntry.{
          id: "bar3",
          size: (123, 321),
          children:
            CompareEntry.{
              added: [],
              removed: [],
              modified: [bar2],
              intact: [],
            },
          reasons: ([], []),
          original: None,
          stat:
            ModifiedEntry.Data.make(
              Entry.Data.make(Some("I am one another bar"), Some(123)),
              Entry.Data.make(
                Some("I am another version of one another bar"),
                Some(321),
              ),
            ),
          parsed: None,
        };
      let comp =
        CompareEntry.{
          added: [],
          removed: [foo1],
          modified: [bar3],
          intact: [],
        };

      let kind =
        CompareEntry.kind(
          comp,
          Entry(foo2),
          [ModifiedEntry(bar2), ModifiedEntry(bar3)],
        );

      expect(kind) |> toEqual(CompareKind.Added);
    });
  });
});
