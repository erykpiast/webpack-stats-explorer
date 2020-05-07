open Rationale.Function.Infix;;

let rec flattenEntries entries =
  List.fold_left (fun (acc: Entry.t list) (entry: Entry.t) ->
    let withChildren = Entry.{ entry with children = [] }::(flattenEntries entry.children)
    in [acc; withChildren] |> List.flatten
  ) [] entries
;;

let parsePath = Utils.String.split "/" ||> Array.to_list ||> List.tl;;

let partitionEntries id = List.partition (fun (e: Entry.t) -> e.id == id);;

exception NotUniqueIdExn;;

let make (entry: Entry.t) =
  let rec addEntry (acc: Entry.t) path (entry: Entry.t) =
    match path with
    | [] -> acc
    | id::pathRest ->
      let (entryChild, otherChildren) =
        match partitionEntries id acc.children with
        | ([], allChildren) ->
          let intermediateEntry =
            match pathRest with
            | [] -> Entry.({ entry with id })
            | _ -> Entry.(
              { id
              ; size = 0
              ; original = None
              ; stat = None
              ; parsed = None
              ; children = []
              })
          in (intermediateEntry, allChildren)
        | ([existingEntry], otherChildren) ->
          let actualEntry =
            if existingEntry.size != 0 || pathRest != [] then
              existingEntry
            else
               Entry.(
                { existingEntry with size = entry.size
                ; stat = entry.stat
                ; original = entry.original
                ; parsed = entry.parsed
                })
          in (actualEntry, otherChildren)
        | _ -> raise NotUniqueIdExn
      in Entry.(
        { acc with size = acc.size + entry.size
        ; children = (addEntry entryChild pathRest entry)::otherChildren
        })
  in [entry]
    |> flattenEntries
    |> List.fold_left
      (fun acc (entry: Entry.t) -> addEntry acc (parsePath entry.id) entry)
      Entry.(
        { id = entry.id
        ; size = 0
        ; original = None
        ; stat = None
        ; parsed = None
        ; children = []
        })
;;
