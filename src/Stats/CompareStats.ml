open Rationale.Function.Infix

let make rebuildSourceTree =
  WebpackStats.sortByBuildTime
  ||> List.map Entry.FromStats.make
  ||> (
    match rebuildSourceTree with
    | true -> List.map (List.map SourceTree.make)
    | false -> List.map (List.map WebpackTree.make)
  ) ||> List.fold_left (
      fun acc a -> match acc with
      | (None, []) -> (
        Some a,
        []
      )
      | (Some b, acc) -> (
          Some a,
          (CompareEntry.make b a) :: acc
        )
      | _ -> acc
  ) (None, [])
  ||> snd
  ||> List.rev
;;