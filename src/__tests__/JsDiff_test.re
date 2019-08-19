open Jest;
open ExpectJs;

describe("JsDiff", () =>
  JsDiff.(
    describe("diffLines", () => {
      test("the same text", () => {
        let str = "foo\nbar";
        let diff = make(str, str);

        expect(diff) |> toEqual([Intact(str)]);
      });

      test("one line completely changed", () => {
        let str1 = "foo";
        let str2 = "bar";
        let diff = make(str1, str2);

        expect(diff) |> toEqual([Removed(str1), Added(str2)]);
      });

      test("two lines completely changed", () => {
        let str1 = "foo\nbar";
        let str2 = "baz\ntaz";
        let diff = make(str1, str2);

        expect(diff) |> toEqual([Removed(str1), Added(str2)]);
      });

      test("line removed between", () => {
        let str1 = "foo\nbar\nbaz";
        let str2 = "foo\nbaz";
        let diff = make(str1, str2);

        expect(diff)
        |> toEqual([Intact("foo\n"), Removed("bar\n"), Intact("baz")]);
      });

      test("line added at the end", () => {
        let str1 = "foo\nbar\n";
        let str2 = "foo\nbar\nbaz";
        let diff = make(str1, str2);

        expect(diff) |> toEqual([Intact("foo\nbar\n"), Added("baz")]);
      });
    })
  )
);