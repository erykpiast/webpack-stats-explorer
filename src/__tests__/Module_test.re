open Jest;
open ExpectJs;

describe("Module", () => {
  open Module;

  describe("normalize name", () => {
    test("same name for already normalized", () =>
      expect(normalizeName("foo")) |> toEqual("foo")
    );

    test("just a name for name with submodules", () =>
      expect(normalizeName("foo + 3 modules")) |> toEqual("foo")
    );

    test("same name for the same module with different submodules", () =>
      expect(normalizeName("foo + 3 modules"))
      |> toEqual(normalizeName("foo + 1 module"))
    );

    test("same name but with different compiler prefix", () =>
      expect(normalizeName("multi foo")) |> toEqual("multi foo")
    );

    test("same name but with different plugin prefix", () =>
      expect(normalizeName("css foo")) |> toEqual("css foo")
    );

    test("same name but with different loader prefix", () =>
      expect(normalizeName("bar!baz!foo")) |> toEqual("foo")
    );
  });

  describe("eql", () => {
    let fakeModule = (name, size, source, modules) =>
      make(
        [],
        false,
        false,
        [],
        0,
        0,
        false,
        None,
        "",
        Some(0),
        Some(0),
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
        0,
      );

    test("module with different name", () => {
      let a = fakeModule("foo", 0, None, None);
      let b = fakeModule("bar", 0, None, None);

      expect(Module.eql(a, b)) |> toEqual(false);
    });

    test("module with different size", () => {
      let a = fakeModule("foo", 0, None, None);
      let b = fakeModule("foo", 1, None, None);

      expect(Module.eql(a, b)) |> toEqual(false);
    });

    test("module with different source", () => {
      let a = fakeModule("foo", 0, Some("foo"), None);
      let b = fakeModule("foo", 0, Some("bar"), None);

      expect(Module.eql(a, b)) |> toEqual(false);
    });

    test("module with different modules", () => {
      let a = fakeModule("foo", 0, Some("bar"), Some([]));
      let b =
        fakeModule(
          "foo",
          0,
          Some("bar"),
          Some([fakeModule("bar", 0, None, None)]),
        );

      expect(Module.eql(a, b)) |> toEqual(false);
    });

    test("module with equal name, size, source and modules", () => {
      let c = fakeModule("bar", 0, None, None);
      let a = fakeModule("foo", 0, Some("bar"), Some([c]));
      let b = fakeModule("foo", 0, Some("bar"), Some([c]));

      expect(Module.eql(a, b)) |> toEqual(true);
    });
  });
});