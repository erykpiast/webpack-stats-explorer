let rec make (entry: Entry.t) =
    let summarizeChildrenSize = List.fold_left (fun acc (child: Entry.t) -> acc + child.size) 0
    in Entry.(
    { entry with size = (
        match entry.size with
        | 0 -> summarizeChildrenSize entry.children
        | size -> size
      )
    ; children = List.map make entry.children
    })
;;