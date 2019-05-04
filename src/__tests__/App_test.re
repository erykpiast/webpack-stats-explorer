open Jest;
open ExpectJs;

describe("App", () =>
  App.(
    describe("update navigation path", () => {
      test("updating last element", () => {
        let path = updateNavigationPath([1, 2, 3], 4, 2);

        expect(path) |> toEqual([1, 2, 4]);
      });

      test("shortening path", () => {
        let path = updateNavigationPath([1, 2, 3], 4, 1);

        expect(path) |> toEqual([1, 4]);
      });

      test("extending path", () => {
        let path = updateNavigationPath([1, 2], 3, 2);

        expect(path) |> toEqual([1, 2, 3]);
      });

      test("adding above path length", () => {
        let path = updateNavigationPath([1, 2, 3], 4, 10);

        expect(path) |> toEqual([1, 2, 3, 4]);
      });

      test("adding to empty path", () => {
        let path = updateNavigationPath([], 1, 0);

        expect(path) |> toEqual([1]);
      });
    })
  )
);