type 'a t =
  { added : 'a list
  ; intact : 'a list
  ; modified : ('a * 'a) list
  ; removed : 'a list
  }

let create isSimilar isEqual xs ys =
  let diff = Utils.List.diff isSimilar
  and intact, modified =
    Utils.List.intersect isSimilar xs ys
    |> List.map (fun z ->
           let findSimilar = List.find (isSimilar z) in
           findSimilar xs, findSimilar ys)
    |> List.partition (fun (x, y) -> isEqual x y)
  in
  { added = diff ys xs; intact = intact |> List.map fst; modified; removed = diff xs ys }
;;

let encode encoder r =
  Json.Encode.(
    object_
      [ "added", r.added |> list encoder
      ; "intact", r.intact |> list encoder
      ; "modified", r.modified |> list (tuple2 encoder encoder)
      ; "removed", r.removed |> list encoder
      ])
;;