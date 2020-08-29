open Jest;
open ExpectJs;

describe("SourceTree", () => {
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
      reasons: [],
    };

  describe("make", () => {
    test("no children", () => {
      let rebuilt = mockEntry(~code="foobar", "./foo") |> SourceTree.make;
      let expected =
        mockEntry(~children=[mockEntry(~code="foobar", "foo")], "./foo");

      expect(rebuilt) |> toEqual(expected);
    });

    test("one child", () => {
      let rebuilt =
        mockEntry(
          ~size=666,
          ~children=[mockEntry(~size=333, ~code="foobar", "./foo/bar")],
          "./foo",
        )
        |> SourceTree.make;
      let expected =
        mockEntry(
          ~size=999,
          ~children=[
            mockEntry(
              ~size=999,
              ~children=[mockEntry(~size=333, ~code="foobar", "bar")],
              "foo",
            ),
          ],
          "./foo",
        );

      expect(rebuilt) |> toEqual(expected);
    });

    test("two children", () => {
      let rebuilt =
        mockEntry(
          ~size=666,
          ~children=[
            mockEntry(~size=222, ~code="foobar", "./foo/bar"),
            mockEntry(~size=444, ~code="barbaz", "./foo/baz"),
          ],
          "./foo",
        )
        |> SourceTree.make;
      let expected =
        mockEntry(
          ~size=1332,
          ~children=[
            mockEntry(
              ~size=1332,
              ~children=[
                mockEntry(~size=444, ~code="barbaz", "baz"),
                mockEntry(~size=222, ~code="foobar", "bar"),
              ],
              "foo",
            ),
          ],
          "./foo",
        );

      expect(rebuilt) |> toEqual(expected);
    });

    test("grandchild", () => {
      let rebuilt =
        mockEntry(
          ~size=666,
          ~children=[mockEntry(~size=444, ~code="foobar", "./foo/bar/baz")],
          "./foo",
        )
        |> SourceTree.make;
      let expected =
        mockEntry(
          ~size=1110,
          ~children=[
            mockEntry(
              ~size=1110,
              ~children=[
                mockEntry(
                  ~size=444,
                  ~children=[mockEntry(~size=444, ~code="foobar", "baz")],
                  "bar",
                ),
              ],
              "foo",
            ),
          ],
          "./foo",
        );

      expect(rebuilt) |> toEqual(expected);
    });

    test("grandchild with parent", () => {
      let rebuilt =
        mockEntry(
          ~size=666,
          ~children=[
            mockEntry(~size=222, ~code="foobar", "./foo/bar"),
            mockEntry(~size=444, ~code="barbaz", "./foo/bar/baz"),
          ],
          "./foo",
        )
        |> SourceTree.make;
      let expected =
        mockEntry(
          ~size=1332,
          ~children=[
            mockEntry(
              ~size=1332,
              ~children=[
                mockEntry(
                  ~size=666,
                  ~code="foobar",
                  ~children=[mockEntry(~size=444, ~code="barbaz", "baz")],
                  "bar",
                ),
              ],
              "foo",
            ),
          ],
          "./foo",
        );

      expect(rebuilt) |> toEqual(expected);
    });

    test("nested", () => {
      let rebuilt =
        mockEntry(
          ~size=666,
          ~children=[
            mockEntry(~size=222, "./bar"),
            mockEntry(~size=444, "./foo/bar"),
            mockEntry(~size=666, "./foo/baz/qux"),
            mockEntry(~size=333, "./foo/baz/fux"),
          ],
          "./foo",
        )
        |> SourceTree.make;
      let expected =
        mockEntry(
          ~size=2331,
          ~children=[
            mockEntry(
              ~size=2109,
              ~children=[
                mockEntry(
                  ~size=999,
                  ~children=[
                    mockEntry(~size=333, "fux"),
                    mockEntry(~size=666, "qux"),
                  ],
                  "baz",
                ),
                mockEntry(~size=444, "bar"),
              ],
              "foo",
            ),
            mockEntry(~size=222, "bar"),
          ],
          "./foo",
        );

      expect(rebuilt) |> toEqual(expected);
    });

    test("duplicated entry", () => {
      let rebuilt =
        mockEntry(
          ~size=0,
          ~children=[
            mockEntry(~size=0, "./foo/bar"),
            mockEntry(~size=222, ~code="foobar", "./foo/bar"),
            mockEntry(~size=444, ~code="barbaz", "./foo/baz"),
          ],
          "./foo",
        )
        |> SourceTree.make;
      let expected =
        mockEntry(
          ~size=666,
          ~children=[
            mockEntry(
              ~size=666,
              ~children=[
                mockEntry(~size=444, ~code="barbaz", "baz"),
                mockEntry(~size=222, ~code="foobar", "bar"),
              ],
              "foo",
            ),
          ],
          "./foo",
        );

      expect(rebuilt) |> toEqual(expected);
    });
  });
});
