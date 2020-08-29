open Jest;
open ExpectJs;

describe("ModifiedEntry", () => {
  let makeModified = ModifiedEntry.make((_, _) => []);

  test("entires with matching fields", () => {
    let e1 =
      Entry.{
        id: "foo",
        size: 666,
        original: None,
        parsed: None,
        children: [],
        stat: Entry.Data.make(Some("I am Foo"), Some(666)),
        reasons: [],
      };
    let e2 =
      Entry.{
        id: "foo",
        size: 555,
        original: None,
        parsed: None,
        children: [],
        stat: Entry.Data.make(Some("I am new Foo"), Some(555)),
        reasons: [],
      };
    let modified = makeModified(e1, e2);

    expect(modified)
    |> toEqual(
         ModifiedEntry.{
           id: "foo",
           size: (666, 555),
           original: None,
           parsed: None,
           children: [],
           reasons: ([], []),
           stat:
             ModifiedEntry.Data.make(
               Entry.Data.make(Some("I am Foo"), Some(666)),
               Entry.Data.make(Some("I am new Foo"), Some(555)),
             ),
         },
       );
  });

  test("entries with extra fields on the right side", () => {
    let e1 =
      Entry.{
        id: "foo",
        size: 666,
        children: [],
        original: None,
        parsed: None,
        stat: Entry.Data.make(Some("I am Foo"), Some(666)),
        reasons: [],
      };
    let e2 =
      Entry.{
        id: "foo",
        size: 222,
        children: [],
        original: None,
        parsed: Entry.Data.make(Some("I'm nu foo"), Some(222)),
        stat: Entry.Data.make(Some("I am new Foo"), Some(555)),
        reasons: [],
      };
    let modified = makeModified(e1, e2);

    expect(modified)
    |> toEqual(
         ModifiedEntry.{
           id: "foo",
           size: (666, 222),
           original: None,
           parsed: None,
           children: [],
           reasons: ([], []),
           stat:
             ModifiedEntry.Data.make(
               Entry.Data.make(Some("I am Foo"), Some(666)),
               Entry.Data.make(Some("I am new Foo"), Some(555)),
             ),
         },
       );
  });

  test("entries with missing fields on the right side", () => {
    let e1 =
      Entry.{
        id: "foo",
        size: 222,
        children: [],
        original: None,
        parsed: Entry.Data.make(Some("I'm nu foo"), Some(222)),
        stat: Entry.Data.make(Some("I am Foo"), Some(666)),
        reasons: [],
      };
    let e2 =
      Entry.{
        id: "foo",
        size: 555,
        children: [],
        original: None,
        parsed: None,
        stat: Entry.Data.make(Some("I am new Foo"), Some(555)),
        reasons: [],
      };
    let modified = makeModified(e1, e2);

    expect(modified)
    |> toEqual(
         ModifiedEntry.{
           id: "foo",
           size: (222, 555),
           original: None,
           parsed: None,
           children: [],
           reasons: ([], []),
           stat:
             ModifiedEntry.Data.make(
               Entry.Data.make(Some("I am Foo"), Some(666)),
               Entry.Data.make(Some("I am new Foo"), Some(555)),
             ),
         },
       );
  });
});
