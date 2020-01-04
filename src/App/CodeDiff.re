open Rationale.Function.Infix;

[@react.component]
let make = (~after, ~before, ~className) => {
  let diff = JsDiff.make(after, before);
  let diffString =
    diff
    |> List.map(
         JsDiff.(
           diff =>
             switch (diff) {
             | Intact(value) => value
             | Added(value) => value
             | Removed(value) => value
             }
         ),
       )
    |> Array.of_list
    |> Utils.Array.join("\n");
  let mapLines = mapper => Utils.String.split("\n") ||> Array.map(mapper) ||> Array.to_list;
  let diffMap =
    diff
    |> List.map(
         JsDiff.(
           diff =>
             switch (diff) {
             | Intact(value) => value |> mapLines((line) => Intact(line))
             | Added(value) => value |> mapLines((line) => Added(line))
             | Removed(value) => value |> mapLines((line) => Removed(line))
             }
         ),
       )
    |> List.flatten
    |> List.nth_opt
    ||> Utils.defaultTo(JsDiff.Intact(""));

  <Code className diffMap> diffString </Code>;
};