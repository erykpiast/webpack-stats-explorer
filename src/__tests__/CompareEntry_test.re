open Jest;
open ExpectJs;

describe("CompareEntry", () => {
  let makeModified = ModifiedEntry.make((_, _) => CompareEntry.make([], []));

  let foo1 =
    Entry.{
      id: "foo",
      size: 666,
      original: None,
      parsed: None,
      stat: Entry.Data.make(Some("I am foo"), Some(666)),
      children: [],
    };
  let foo2 =
    Entry.{
      id: "foo",
      size: 555,
      original: None,
      parsed: None,
      stat: Entry.Data.make(Some("I am different foo"), Some(555)),
      children: [],
    };
  let bar1 =
    Entry.{
      id: "bar",
      size: 555,
      original: None,
      parsed: None,
      stat: Entry.Data.make(Some("I am Boo"), Some(555)),
      children: [],
    };

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
});