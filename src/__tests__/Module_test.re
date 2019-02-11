open Jest;
open ExpectJs;

describe("Module", () => {
  describe("eql", () => {
    open Module;

    let fakeModule = (name, size, source, modules) => make(
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
      let b = fakeModule("foo", 0, Some("bar"), Some([
        fakeModule("bar", 0, None, None)
      ]));

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
