open Jest;
open ExpectJs;

describe("WebpackTree", () => {
  let mockEntry = (~children=[], ~size=666, ~code="", id) =>
    Entry.{
      id,
      size,
      original: None,
      stat:
        switch (code) {
        | "" => None
        | code => Entry.Data.make(Some(code), Some(String.length(code)))
        },
      parsed: None,
      children,
    };

  describe("make", () => {
    test("no children", () => {
      let input = mockEntry(~code="foobar", "./foo");
      let output = input |> WebpackTree.make;

      expect(output) |> toEqual(input);
    });

    test("all children with size", () => {
      let input =
        mockEntry(
          ~size=666,
          ~children=[
            mockEntry(
              ~size=222,
              ~code="foobar",
              "./foo/bar",
              ~children=[
                mockEntry(~size=111, ~code="bazqux", "./foo/bar/baz"),
              ],
            ),
            mockEntry(~size=444, ~code="barbaz", "./foo/baz"),
          ],
          "./foo",
        );
      let output = input |> WebpackTree.make;

      expect(output) |> toEqual(input);
    });

    test("child without size", () => {
      let input =
        mockEntry(
          ~size=666,
          ~children=[
            mockEntry(
              ~size=0,
              ~code="",
              "./foo/bar",
              ~children=[
                mockEntry(~size=111, ~code="bazqux", "./foo/bar/baz"),
                mockEntry(~size=222, ~code="quxfaz", "./foo/bar/qux"),
              ],
            ),
            mockEntry(~size=444, ~code="barbaz", "./foo/baz"),
          ],
          "./foo",
        );
      let output = input |> WebpackTree.make;
      let expected =
        mockEntry(
          ~size=666,
          ~children=[
            mockEntry(
              ~size=333,
              ~code="",
              "./foo/bar",
              ~children=[
                mockEntry(~size=111, ~code="bazqux", "./foo/bar/baz"),
                mockEntry(~size=222, ~code="quxfaz", "./foo/bar/qux"),
              ],
            ),
            mockEntry(~size=444, ~code="barbaz", "./foo/baz"),
          ],
          "./foo",
        );

      expect(output) |> toEqual(expected);
    });
  });
});