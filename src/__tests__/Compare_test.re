open Jest;
open ExpectJs;

describe("Compare", () => {
  open Compare;

  describe("Chunks", () => {
    open Chunks;

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

        let result = similar(a, b);

        expect(result) |> toEqual(true);
      });

      test("equal files and empty names", () => {
        let a = fakeChunk(["foo", "bar"], []);
        let b = fakeChunk(["foo", "bar"], []);

        let result = similar(a, b);

        expect(result) |> toEqual(true);
      });

      test("different files and empty names", () => {
        let a = fakeChunk(["foo", "bar"], []);
        let b = fakeChunk(["foo", "baz"], []);

        let result = similar(a, b);

        expect(result) |> toEqual(false);
      });

      test("different files but equal names", () => {
        let a = fakeChunk(["foo", "bar"], ["bar", "baz"]);
        let b = fakeChunk(["foo", "baz"], ["bar", "baz"]);

        let result = similar(a, b);

        expect(result) |> toEqual(true);
      });

      test("different files and names", () => {
        let a = fakeChunk(["foo", "bar"], ["bar", "baz"]);
        let b = fakeChunk(["foo", "baz"], ["bar", "taz"]);

        let result = similar(a, b);

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

      test("calcSize", () => {
        let result = calcSize([foo1, bar1, baz1, taz1]);

        expect(result) |> toEqual(1000);
      });

      describe("make", () => {
        let a = [baz1, foo1, bar1];
        let b = [foo2, bar2, taz2];
        let result = make(a, b);

        test("chunks existing in both sets and changed", () => {
          expect(result.modified) |> toEqual([ModifiedSummary.make(Summary.make, foo1, foo2)]);
        });

        test("chunks existing in both sets and not changed", () => {
          expect(result.intact) |> toEqual([Summary.make(bar2)]);
        });

        test("chunks present only in the second set", () => {
          expect(result.added) |> toEqual([Summary.make(taz2)]);
        });

        test("chunks present only in the first set", () => {
          expect(result.removed) |> toEqual([Summary.make(baz1)]);
        });
      });
    });
  });

  describe("Modules", () => {
    open Modules;

    let fakeModule = (name, size, source, modules) => Module.make(
      [],
      false,
      false,
      [],
      0,
      0,
      false,
      None,
      "",
      0,
      0,
      None,
      None,
      None,
      None,
      modules,
      name,
      [],
      false,
      false,
      None,
      None,
      [],
      size,
      source,
      None,
      0
    );

    let foo = fakeModule("foo", 100, Some("foo"), None);
    let foo2 = fakeModule("foo", 200, Some("foo2"), None);
    let bar = fakeModule("bar", 200, Some("bar"), Some([]));
    let bar2 = fakeModule("bar", 400, Some("bar2"), Some([]));
    let baz = fakeModule("baz", 100, Some("baz"), Some([bar]));
    let baz2 = fakeModule("baz", 100, Some("baz"), Some([bar2]));
    let taz = fakeModule("taz", 100, None, Some([foo, baz]));
    let taz2 = fakeModule("taz", 100, None, Some([bar, baz2]));
    let faz = fakeModule("faz", 100, None, Some([foo, bar]));
    let faz2 = fakeModule("faz", 100, None, Some([foo, bar]));

    describe("summary", () => {
      open Summary;

      let withSource = make(foo);
      let withSubmodules = make(taz);

      test("source", () => {
        expect(withSource.source) |> toEqual("foo");
      });

      test("modules", () => {
        expect(withSubmodules.modules) |> toEqual([
          make(foo),
          make(baz)
        ]);
      });
    });

    describe("diff simple case", () => {
      let modules1 = [foo, baz, taz, faz];
      let modules2 = [bar2, baz2, taz2, faz2];
      let result = make(modules1, modules2);

      test("added", () => {
        expect(result.added) |> toEqual([Summary.make(bar2)])
      });

      test("removed", () => {
        expect(result.removed) |> toEqual([Summary.make(foo)])
      });

      test("intact", () => {
        expect(result.intact) |> toEqual([Summary.make(faz2)])
      });
    });
  });
});