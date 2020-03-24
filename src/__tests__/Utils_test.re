open Jest;
open ExpectJs;
open BsJsverify;

describe("Utils", () =>
  describe("List", () => {
    open Utils.List;

    describe("equal", () => {
      test("false for lists with different length", () => {
        let result = isEqual([1, 2], [1, 2, 3], ());

        expect(result) |> toEqual(false);
      });

      test("false for lists with the same length but different elements", () => {
        let result = isEqual([1, 2], [3, 4], ());

        expect(result) |> toEqual(false);
      });

      test("false for lists with the same elements in different order", () => {
        let result = isEqual([1, 2], [2, 1], ());

        expect(result) |> toEqual(false);
      });

      test(
        "true for lists with the same length and the same elements in the same order",
        () => {
        let result = isEqual([1, 2], [1, 2], ());

        expect(result) |> toEqual(true);
      });

      test("true for two empty lists", () => {
        let result = isEqual([], [], ());

        expect(result) |> toEqual(true);
      });

      test(
        "false for two equal lists and eql function always returning false", () => {
        let result = isEqual([1, 2], [1, 2], ~eql=(_, _) => false, ());

        expect(result) |> toEqual(false);
      });

      test(
        "false for two lists with different length and eql function always returning true",
        () => {
          let result = isEqual([1, 2], [3, 4, 5], ~eql=(_, _) => true, ());

          expect(result) |> toEqual(false);
        },
      );

      test(
        "true for two different lists with the same length and eql function always returning true",
        () => {
          let result =
            isEqual([1, 2, 3], [4, 5, 6], ~eql=(_, _) => true, ());

          expect(result) |> toEqual(true);
        },
      );

      describe("property", () => {
        open Verify.Arbitrary;
        open Verify.Property;

        let createSuiteForType = (name, type_) =>
          describe(
            "list of " ++ name,
            () => {
              let list = arb_list(type_);
              let listsWithDifferentLengths =
                arb_such_that(
                  arb_tuple((arb_list(type_), arb_list(type_))), ((a, b)) =>
                  List.length(a) != List.length(b)
                );

              property1("true for the same list", list, a =>
                isEqual(a, a, ()) == true
              );

              property1(
                "true for equal list",
                list,
                a => {
                  let b = List.map(Rebase.Fn.id, a);
                  isEqual(a, b, ()) == true;
                },
              );

              property1(
                "false for lists with different lengths",
                listsWithDifferentLengths,
                ((a, b)) =>
                isEqual(a, b, ()) == false
              );

              property2("idempotent", list, list, (a, b) =>
                isEqual(a, b, ()) == isEqual(b, a, ())
              );
            },
          );

        createSuiteForType("ints", arb_int(-100, 100));
        createSuiteForType("floats", arb_float(-100.0, 100.0));
        createSuiteForType("strings", arb_string);
      });
    });

    describe("diff", () => {
      let simpleDiff = diff((a, b) => a == b);

      test("empty list for two empty lists", () => {
        let result = simpleDiff([], []);

        expect(result) |> toEqual([]);
      });

      test("empty list for equal lists", () => {
        let result = simpleDiff([1, 2], [1, 2]);

        expect(result) |> toEqual([]);
      });

      test(
        "list with elements not in second list when lists are different", () => {
        let a = [2, 3];
        let b = [1, 2];

        expect(simpleDiff(a, b)) |> toEqual([3]) |> ignore;
        expect(simpleDiff(b, a)) |> toEqual([1]);
      });
    });

    describe("uniq", () => {
      let simpleUniq = uniq((a, b) => a == b);

      test("empty for empty list", () => {
        let result = simpleUniq([]);

        expect(result) |> toEqual([]);
      });

      test("list for list with unique elements", () => {
        let list = [1, 2, 3];
        let result = simpleUniq(list);

        expect(result) |> toEqual(list);
      });

      test("list without dupicated elements", () => {
        let result = simpleUniq([1, 1, 2, 2, 3, 3]);

        expect(result) |> toEqual([1, 2, 3]);
      });
    });

    describe("intersect", () => {
      let simpleIntersect = intersect((a, b) => a == b);

      test("empty list for two empty lists", () => {
        let result = simpleIntersect([], []);

        expect(result) |> toEqual([]);
      });

      test("equal list for equal lists", () => {
        let result = simpleIntersect([1, 2], [1, 2]);

        expect(result) |> toEqual([1, 2]);
      });

      test("list with elements in both lists when lists are different", () => {
        let a = [2, 3];
        let b = [1, 2];

        expect(simpleIntersect(a, b)) |> toEqual([2]);
      });

      test("unique list when intersected element is duplicated in one", () => {
        let a = [1, 1];
        let b = [1, 2];

        expect(simpleIntersect(a, b)) |> toEqual([1]);
      });

      describe("property", () => {
        open Verify.Arbitrary;
        open Verify.Property;

        let createSuiteForType = (name, type_) =>
          describe(
            "list of " ++ name,
            () => {
              let list = arb_list(type_);
              let isEqual = (a, b) => a == b;

              property2("idempotent", list, list, (a, b) =>
                List.sort(compare, intersect(isEqual, a, b))
                == List.sort(compare, intersect(isEqual, b, a))
              );
            },
          );

        createSuiteForType("ints", arb_int(-100, 100));
        createSuiteForType("floats", arb_float(-100.0, 100.0));
        createSuiteForType("strings", arb_string);
      });
    });

    describe("prepend", () => {
       test("single element list for empty list", () => {
        let result = prepend(1, []);

        expect(result) |> toEqual([1]);
      });

      test("two elements list for single element list", () => {
        let result = prepend(1, [2]);

        expect(result) |> toEqual([1, 2]);
      });

      test("three elements list for two element list", () => {
        let result = prepend(1, [2, 3]);

        expect(result) |> toEqual([1, 2, 3]);
      });
    });
  })
);
