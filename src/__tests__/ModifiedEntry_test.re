open Jest;
open ExpectJs;

describe("ModifiedEntry", () => {
  let makeModified = ModifiedEntry.make((_, _) => []);

  test("entires with matching fields", () => {
    let e1 =
      Entry.{
        id: "foo",
        original: None,
        parsed: None,
        children: [],
        stat: Some(Entry.Data.{source: "I am Foo", size: 666}),
      };
    let e2 =
      Entry.{
        id: "foo",
        original: None,
        parsed: None,
        children: [],
        stat: Some(Entry.Data.{source: "I am new Foo", size: 555}),
      };
    let modified = makeModified(e1, e2);

    expect(modified)
    |> toEqual(
         ModifiedEntry.{
           id: "foo",
           original: None,
           parsed: None,
           children: [],
           stat:
             Some(
               ModifiedEntry.Data.{
                 size: (666, 555),
                 source: ("I am Foo", "I am new Foo"),
               },
             ),
         },
       );
  });

  test("entries with extra fields on the right side", () => {
    let e1 =
      Entry.{
        id: "foo",
        children: [],
        original: None,
        parsed: None,
        stat: Some(Entry.Data.{source: "I am Foo", size: 666}),
      };
    let e2 =
      Entry.{
        id: "foo",
        children: [],
        original: None,
        parsed: Some(Entry.Data.{source: "I'm nu foo", size: 222}),
        stat: Some(Entry.Data.{source: "I am new Foo", size: 555}),
      };
    let modified = makeModified(e1, e2);

    expect(modified)
    |> toEqual(
         ModifiedEntry.{
           id: "foo",
           original: None,
           parsed: None,
           children: [],
           stat:
             Some(
               ModifiedEntry.Data.{
                 size: (666, 555),
                 source: ("I am Foo", "I am new Foo"),
               },
             ),
         },
       );
  });

  test("entries with missing fields on the right side", () => {
    let e1 =
      Entry.{
        id: "foo",
        children: [],
        original: None,
        parsed: Some(Entry.Data.{source: "I'm nu foo", size: 222}),
        stat: Some(Entry.Data.{source: "I am Foo", size: 666}),
      };
    let e2 =
      Entry.{
        id: "foo",
        children: [],
        original: None,
        parsed: None,
        stat: Some(Entry.Data.{source: "I am new Foo", size: 555}),
      };
    let modified = makeModified(e1, e2);

    expect(modified)
    |> toEqual(
         ModifiedEntry.{
           id: "foo",
           original: None,
           parsed: None,
           children: [],
           stat:
             Some(
               ModifiedEntry.Data.{
                 size: (666, 555),
                 source: ("I am Foo", "I am new Foo"),
               },
             ),
         },
       );
  });
});