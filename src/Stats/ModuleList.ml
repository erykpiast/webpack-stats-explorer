let make (entry: Entry.t) =
  let rec flatten (child: Entry.t) =
    let children = child.children
      |> List.map flatten
      |> List.flatten
      |> List.filter (fun (entry: Entry.t) -> entry.size > 0)
    in { child with children = [] }::children
  in { entry with children = entry |> flatten |> List.tl }
;;