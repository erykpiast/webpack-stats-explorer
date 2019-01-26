/* Component_test.re */

open Jest;
open ExpectJs;

describe("Compare", () => {
  describe("Chunks", () => {
    open Compare;

    describe("chunksSimilar", () => {
      let fakeChunk = (files, names) => Chunk.make(
        Js.Dict.empty(),
        false,
        files,
        0,
        "",
        0,
        false,
        [],
        names,
        [],
        [],
        false,
        [],
        0
      );

      test("equal files and different names", () => {
        let a = fakeChunk(["foo", "bar"], ["bar"]);
        let b = fakeChunk(["foo", "bar"], ["baz"]);

        let result = chunksSimilar(a, b);

        expect(result) |> toEqual(true);
      });

      test("equal files and empty names", () => {
        let a = fakeChunk(["foo", "bar"], []);
        let b = fakeChunk(["foo", "bar"], []);

        let result = chunksSimilar(a, b);

        expect(result) |> toEqual(true);
      });

      test("different files and empty names", () => {
        let a = fakeChunk(["foo", "bar"], []);
        let b = fakeChunk(["foo", "baz"], []);

        let result = chunksSimilar(a, b);

        expect(result) |> toEqual(false);
      });

      test("different files but equal names", () => {
        let a = fakeChunk(["foo", "bar"], ["bar", "baz"]);
        let b = fakeChunk(["foo", "baz"], ["bar", "baz"]);

        let result = chunksSimilar(a, b);

        expect(result) |> toEqual(true);
      });

      test("different files and names", () => {
        let a = fakeChunk(["foo", "bar"], ["bar", "baz"]);
        let b = fakeChunk(["foo", "baz"], ["bar", "taz"]);

        let result = chunksSimilar(a, b);

        expect(result) |> toEqual(false);
      });
    });

    describe("compare", () => {
      let fakeChunk = (files, names, size) => Chunk.make(
        Js.Dict.empty(),
        false,
        files,
        0,
        "",
        0,
        false,
        [],
        names,
        [],
        [],
        false,
        [],
        size
      );
      let foo1 = fakeChunk(["foo123"], ["foo"], 100);
      let foo2 = fakeChunk(["foo456"], ["foo"], 200);
      let bar1 = fakeChunk(["bar123"], ["bar"], 200);
      let bar2 = fakeChunk(["bar123"], ["bar"], 200);
      let baz1 = fakeChunk(["baz123"], ["baz"], 300);
      let baz2 = fakeChunk(["baz456"], ["baz"], 400);
      let taz1 = fakeChunk(["taz123"], ["taz"], 400);
      let taz2 = fakeChunk(["taz456"], ["taz"], 300);

      describe("diffChunks", () => {
        let a = [baz1, foo1, bar1];
        let b = [foo2, bar2, taz2];
        let result = diffChunks(a, b);

        test("chunks existing in both sets and changed", () => {
          expect(result.modified) |> toEqual([(foo1, foo2)]);
        });

        test("chunks existing in both sets and not changed", () => {
          expect(result.intact) |> toEqual([bar2]);
        });

        test("chunks present only in the second set", () => {
          expect(result.added) |> toEqual([taz2]);
        });

        test("chunks present only in the first set", () => {
          expect(result.removed) |> toEqual([baz1]);
        });
      });

      test("calcSize", () => {
        let result = calcSize([foo1, bar1, baz1, taz1]);

        expect(result) |> toEqual(1000);
      });
    });
  });
});