open Rationale.Function.Infix

let make =
  List.sort (fun (a: WebpackStats.t) (b: WebpackStats.t) -> a.builtAt - b.builtAt)
  ||> (List.map (fun (stat: WebpackStats.t) ->
    stat.chunks |> List.map (Entry.FromChunk.make stat.assets)
  ))
  ||> List.fold_left (
      fun acc a -> match acc with
      | (None, []) -> (Some a, [])
      | (Some b, acc) -> (
          Some a,
          (CompareEntry.make b a) :: acc
        )
      | _ -> acc
  ) (None, [])
  ||> snd
  ||> List.rev
;;