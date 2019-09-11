open Jest;
open ExpectJs;

describe("WelcomeScreen", () =>
  WelcomeScreen.(
    describe("compareStats", () => {
      let mockStats = builtAt =>
        Stats.make(
          [],
          Js.Dict.fromList([]),
          builtAt,
          [],
          [
            Chunk.make(
              Js.Dict.fromList([]),
              false,
              [],
              0,
              "",
              0,
              false,
              [],
              ["chunk"],
              [],
              [],
              true,
              [],
              builtAt,
            ),
          ],
          Js.Dict.fromList([]),
          [],
          0,
          "",
          [],
          Js.Dict.fromList([]),
          "",
          0,
          "",
          [],
        );
      let a = mockStats(1);
      let b = mockStats(2);
      let c = mockStats(3);
      let d = mockStats(4);

      test("one comparision less than stats compared", () => {
        let comparison = compareStats([|a, b, c, d|]);

        expect(comparison |> Array.of_list) |> toHaveLength(3);
      });

      test(
        "uploading multiple stats is equal to doing it one by one sorted by build time",
        () => {
          let comparison = compareStats([|d, a, c, b|]);
          let ab = compareStats([|a, b|]);
          let bc = compareStats([|b, c|]);
          let cd = compareStats([|c, d|]);

          expect(comparison) |> toEqual(List.flatten([ab, bc, cd]));
        },
      );
    })
  )
);