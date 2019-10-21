open Jest;
open ExpectJs;

describe("CompareStats", () => {
  let mockChunk = builtAt =>
    WebpackChunk.{
      childrenByOrder: Js.Dict.fromList([]),
      entry: false,
      files: ["chunk.js"],
      filteredModules: 0,
      hash: "",
      id: 0,
      initial: false,
      modules: [],
      names: ["chunk"],
      origins: [],
      parents: [],
      rendered: true,
      siblings: [],
      size: builtAt,
      parsedSize: None,
    };
  let mockStats = builtAt =>
    WebpackStats.{
      assets: [],
      assetsByChunkName: Js.Dict.fromList([]),
      builtAt,
      children: [],
      chunks: [mockChunk(builtAt)],
      entrypoints: Js.Dict.fromList([]),
      errors: [],
      filteredAssets: 0,
      hash: "",
      modules: [],
      namedChunkGroups: Js.Dict.fromList([]),
      outputPath: "",
      time: 0,
      version: "",
      warnings: [],
    };
  let a = mockStats(1);
  let b = mockStats(2);
  let c = mockStats(3);
  let d = mockStats(4);

  test("one comparision less than stats compared", () => {
    let comparison = CompareStats.make([a, b, c, d]);

    expect(comparison |> Array.of_list) |> toHaveLength(3);
  });

  test(
    "uploading multiple stats is equal to doing it one by one sorted by build time",
    () => {
      let comparison = CompareStats.make([d, a, c, b]);
      let ab = CompareStats.make([a, b]);
      let bc = CompareStats.make([b, c]);
      let cd = CompareStats.make([c, d]);

      expect(comparison) |> toEqual(List.flatten([ab, bc, cd]));
    },
  );
});
