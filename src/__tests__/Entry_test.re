open Jest;
open ExpectJs;

describe("Entry", () => {
  let mockModule =
      (
        ~name,
        ~size,
        ~source=None,
        ~originalSize=None,
        ~originalSource=None,
        ~parsedSize=None,
        ~parsedSource=None,
        ~modules=None,
        ~built=true,
        ~reasons=[],
        (),
      ) =>
    WebpackModule.{
      assets: [],
      built,
      cacheable: false,
      chunks: ["0"],
      depth: 0,
      errors: 0,
      failed: false,
      id: None,
      identifier: "",
      index: None,
      index2: None,
      issuer: None,
      issuerId: None,
      issuerName: None,
      issuerPath: None,
      modules,
      name,
      optimizationBailout: [],
      optional: false,
      prefetched: false,
      profile: None,
      providedExports: None,
      reasons,
      size,
      ownSize: size,
      source,
      originalSize,
      originalSource,
      parsedSize,
      parsedSource,
      usedExports: None,
      warnings: 0,
    };

  describe("FromModule", () => {
    test("module without source", () => {
      let module_ = mockModule(~name="foo", ~size=666, ());
      let entry = Entry.FromModule.make(module_);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "foo",
             size: 666,
             original: None,
             stat: Entry.Data.make(Some(""), Some(666)),
             parsed: None,
             children: [],
           },
         );
    });

    test("module with just a source", () => {
      let module_ =
        mockModule(~name="foo", ~size=666, ~source=Some("I am Foo"), ());
      let entry = Entry.FromModule.make(module_);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "foo",
             size: 666,
             original: None,
             stat: Entry.Data.make(Some("I am Foo"), Some(666)),
             parsed: None,
             children: [],
           },
         );
    });

    test("module with original and parsed sources and sizes", () => {
      let module_ =
        mockModule(
          ~name="foo",
          ~size=666,
          ~source=Some("I am Foo"),
          ~originalSize=Some(999),
          ~originalSource=Some("I am original Foo"),
          ~parsedSize=Some(444),
          ~parsedSource=Some("I'm Foo"),
          (),
        );
      let entry = Entry.FromModule.make(module_);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "foo",
             size: 444,
             original:
               Entry.Data.make(Some("I am original Foo"), Some(999)),
             stat: Entry.Data.make(Some("I am Foo"), Some(666)),
             parsed: Entry.Data.make(Some("I'm Foo"), Some(444)),
             children: [],
           },
         );
    });

    test("module with submodules", () => {
      let submodule1 =
        mockModule(~name="foo", ~size=666, ~source=Some("I am Foo"), ());
      let submodule2 =
        mockModule(~name="bar", ~size=555, ~source=Some("I am Bar"), ());
      let module_ =
        mockModule(
          ~name="baz",
          ~size=444,
          ~source=Some("I am Baz"),
          ~modules=Some([submodule1, submodule2]),
          (),
        );
      let entry = Entry.FromModule.make(module_);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "baz",
             size: 444,
             original: None,
             stat: Entry.Data.make(Some("I am Baz"), Some(444)),
             parsed: None,
             children: [
               Entry.FromModule.make(submodule1),
               Entry.FromModule.make(submodule2),
             ],
           },
         );
    });

    test("module with main submodule", () => {
      let submodule =
        mockModule(~name="foo", ~size=666, ~source=Some("I am Foo"), ());
      let mainSubmodule =
        mockModule(~name="bar", ~size=555, ~source=Some("I am Bar"), ());
      let module_ =
        mockModule(
          ~name="bar",
          ~size=444,
          ~source=None,
          ~modules=Some([submodule, mainSubmodule]),
          (),
        );
      let entry = Entry.FromModule.make(module_);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "bar",
             size: 444,
             original: None,
             stat: Entry.Data.make(Some("I am Bar"), Some(555)),
             parsed: None,
             children: [Entry.FromModule.make(submodule)],
           },
         );
    });

    test("filtering meaningless submodules", () => {
      let notBuilt =
        mockModule(
          ~name="baz",
          ~size=444,
          ~source=Some("I am Baz"),
          ~built=false,
          (),
        );
      let entryPoint =
        mockModule(
          ~name="moo",
          ~size=222,
          ~source=None,
          ~reasons=[
            WebpackReason.{
              module_: None,
              moduleId: None,
              moduleIdentifier: None,
              moduleName: None,
              type_: "some",
              userRequest: "gimme",
              loc: "0",
            },
          ],
          (),
        );
      let withSubmodules =
        mockModule(
          ~name="taz",
          ~size=333,
          ~source=None,
          ~modules=
            Some([
              mockModule(
                ~name="bar",
                ~size=555,
                ~source=Some("I am Bar"),
                (),
              ),
            ]),
          (),
        );
      let withSource =
        mockModule(~name="foo", ~size=666, ~source=Some("I am Foo"), ());
      let module_ =
        mockModule(
          ~name="faz",
          ~size=111,
          ~source=None,
          ~modules=Some([notBuilt, withSource, entryPoint, withSubmodules]),
          (),
        );
      let entry = Entry.FromModule.make(module_);

      expect(entry.children)
      |> toEqual([
           Entry.FromModule.make(withSource),
           Entry.FromModule.make(withSubmodules),
         ]);
    });

    describe("getId", () => {
      test("filepath with loader", () => {
        let id = Entry.FromModule.getId("foo/bar!baz/taz!faz/maz");

        expect(id) |> toEqual("faz/maz");
      });

      test("filepath with ~", () => {
        let id = Entry.FromModule.getId("~/foo/bar");

        expect(id) |> toEqual("node_modules/foo/bar");
      });

      test("filepath with .", () => {
        let id = Entry.FromModule.getId("./foo/bar");

        expect(id) |> toEqual("foo/bar");
      });

      test("filepath with submodules", () => {
        let id = Entry.FromModule.getId("foo/bar + 666 modules");

        expect(id) |> toEqual("foo/bar");
      });

      test("filepath with one submodule", () => {
        let id = Entry.FromModule.getId("foo/bar + 1 module");

        expect(id) |> toEqual("foo/bar");
      });
    });
  });

  describe("FromChunk", () => {
    let mockChunk = (~file, ~name, ~size, ~modules=[], ()) =>
      WebpackChunk.{
        childrenByOrder: Js.Dict.empty(),
        entry: false,
        files: [file],
        filteredModules: 0,
        hash: "",
        id: "0",
        initial: false,
        modules,
        names: [name],
        origins: [],
        parents: [],
        rendered: true,
        siblings: [],
        size,
        parsedSize: Some(size),
      };
    let mockAsset = (~file, ~name, ~size) =>
      WebpackAsset.{
        emitted: Some(false),
        chunkNames: [name],
        chunks: ["0"],
        name: file,
        size,
      };

    test("create entry for chunk and corresponding asset", () => {
      let chunk = mockChunk(~file="foo.js", ~name="foo", ~size=666, ());
      let assets = [mockAsset(~file="foo.js", ~name="foo", ~size=444)];
      let entry = Entry.FromChunk.make(assets, chunk);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "foo",
             size: 444,
             original: None,
             stat: Entry.Data.make(Some(""), Some(666)),
             parsed: Entry.Data.make(Some(""), Some(444)),
             children: [],
           },
         );
    });

    test("should create entry for chunk with no corresponding asset", () => {
      let chunk = mockChunk(~file="foo.js", ~name="foo", ~size=666, ());
      let assets = [];
      let entry = Entry.FromChunk.make(assets, chunk);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "foo",
             size: 666,
             original: None,
             stat: Entry.Data.make(Some(""), Some(666)),
             parsed: None,
             children: [],
           },
         );
    });

    test("should create entry for chunk with submodules", () => {
      let submodule1 =
        mockModule(
          ~name="foo",
          ~originalSize=Some(111),
          ~originalSource=Some("I am original Foo"),
          ~size=0,
          (),
        );
      let submodule2 =
        mockModule(
          ~name="bar",
          ~originalSize=Some(222),
          ~originalSource=Some("I am original Bar"),
          ~size=0,
          (),
        );
      let chunk =
        mockChunk(
          ~file="foo.js",
          ~name="foo",
          ~size=666,
          ~modules=[submodule1, submodule2],
          (),
        );
      let assets = [];
      let entry = Entry.FromChunk.make(assets, chunk);

      expect(entry)
      |> toEqual(
           Entry.{
             id: "foo",
             size: 666,
             original: Entry.Data.make(Some(""), Some(333)),
             stat: Entry.Data.make(Some(""), Some(666)),
             parsed: None,
             children: [
               Entry.FromModule.make(submodule1),
               Entry.FromModule.make(submodule2),
             ],
           },
         );
    });

    test("filtering meaningless submodules", () => {
      let notBuilt =
        mockModule(
          ~name="baz",
          ~size=444,
          ~source=Some("I am Baz"),
          ~built=false,
          (),
        );
      let entryPoint =
        mockModule(
          ~name="moo",
          ~size=222,
          ~source=None,
          ~reasons=[
            WebpackReason.{
              module_: None,
              moduleId: None,
              moduleIdentifier: None,
              moduleName: None,
              type_: "some",
              userRequest: "gimme",
              loc: "0",
            },
          ],
          (),
        );
      let withSubmodules =
        mockModule(
          ~name="taz",
          ~size=333,
          ~source=None,
          ~modules=
            Some([
              mockModule(
                ~name="bar",
                ~size=555,
                ~source=Some("I am Bar"),
                (),
              ),
            ]),
          (),
        );
      let withSource =
        mockModule(~name="foo", ~size=666, ~source=Some("I am Foo"), ());
      let chunk =
        mockChunk(
          ~file="foo.js",
          ~name="foo",
          ~size=666,
          ~modules=[notBuilt, withSource, entryPoint, withSubmodules],
          (),
        );
      let entry = Entry.FromChunk.make([], chunk);

      expect(entry.children)
      |> toEqual([
           Entry.FromModule.make(withSource),
           Entry.FromModule.make(withSubmodules),
         ]);
    });

    describe("getId", () => {
      let mockChunkForId = (~names=[], ~files=[], ()) =>
        WebpackChunk.{
          childrenByOrder: Js.Dict.empty(),
          entry: false,
          files,
          filteredModules: 0,
          hash: "",
          id: "0",
          initial: false,
          modules: [],
          names,
          origins: [],
          parents: [],
          rendered: true,
          siblings: [],
          size: 0,
          parsedSize: None,
        };

      test("chunk with names", () => {
        let chunk = mockChunkForId(~names=["foo", "bar"], ());
        let id = Entry.FromChunk.getId(chunk);

        expect(id) |> toEqual("foo");
      });

      test("chunk without names and with JS files", () => {
        let chunk = mockChunkForId(~files=["foo.css", "bar.js"], ());
        let id = Entry.FromChunk.getId(chunk);

        expect(id) |> toEqual("bar.js");
      });

      test("chunk without names and no JS files", () => {
        let chunk = mockChunkForId(~files=["foo.css", "bar.png"], ());
        let id = Entry.FromChunk.getId(chunk);

        expect(id) |> toEqual("foo.css");
      });

      test("chunk with hashed filename", () => {
        let chunk = mockChunkForId(~files=["foo.abc123.js"], ());
        let id = Entry.FromChunk.getId(chunk);

        expect(id) |> toEqual("foo.js");
      });
    });

    describe("removeHash", () => {
      test("JS file", () => {
        let noHash = Entry.FromChunk.removeHash("foo.1abcde.js");

        expect(noHash) |> toEqual("foo.js");
      });

      test("CSS file", () => {
        let noHash = Entry.FromChunk.removeHash("foo.1abcde.css");

        expect(noHash) |> toEqual("foo.css");
      });

      test("filepath", () => {
        let noHash = Entry.FromChunk.removeHash("foo/bar/baz.1abcde.js");

        expect(noHash) |> toEqual("foo/bar/baz.js");
      });

      test("hash in dirname", () => {
        let noHash = Entry.FromChunk.removeHash("foo.1abcde.bar/baz.js");

        expect(noHash) |> toEqual("foo.1abcde.bar/baz.js");
      });
    });
  });
});
