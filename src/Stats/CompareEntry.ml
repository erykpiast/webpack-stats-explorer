type t =
  { added : Entry.t list
  ; removed : Entry.t list
  ; intact : Entry.t list
  ; modified : t ModifiedEntry.t list
  }
;;

let rec encode r = Json.Encode.(object_
  [ "added", r.added |> list Entry.encode
  ; "removed", r.removed |> list Entry.encode
  ; "intact", r.intact |> list Entry.encode
  ; "modified", r.modified |> list (ModifiedEntry.encode encode)
  ])
;;

let diff = Diff.create Entry.similar Entry.eql

let rec make xs ys =
  let d = diff xs ys
  and makeModified = (ModifiedEntry.make make) |> Utils.Function.uncurry2
  in
  { added = d.added
  ; removed = d.removed
  ; intact = d.intact
  ; modified = d.modified |> List.map makeModified
  }
;;

let count comp =
  (
    [
      comp.intact |> List.length;
      comp.removed |> List.length;
      comp.modified |> List.length
    ] |> Utils.List.sumInt,
    [
      comp.intact |> List.length;
      comp.added |> List.length;
      comp.modified |> List.length
    ] |> Utils.List.sumInt
  )
;;

let size comp = Rationale.Function.Infix.
  (
    let sum = List.flatten ||> Utils.List.sumInt
    and getEntrySize = fun (entry : Entry.t) -> entry.size
    and getModifiedEntrySize = fun (entry : t ModifiedEntry.t) -> entry.size
    in (
      [
        comp.intact |> List.map getEntrySize;
        comp.removed |> List.map getEntrySize;
        comp.modified |> List.map (getModifiedEntrySize ||> fst)
      ] |> sum,
      [
        comp.intact |> List.map getEntrySize;
        comp.added |> List.map getEntrySize;
        comp.modified |> List.map (getModifiedEntrySize ||> snd)
      ] |> sum
    )
  )
;;

let empty =
  { added = []
  ; removed = []
  ; intact = []
  ; modified = []
  }
;;

type entry =
  | Entry of Entry.t
  | ModifiedEntry of t ModifiedEntry.t
;;

let encodeEntry entry =
  match entry with
  | Entry(e) -> Entry.encode e
  | ModifiedEntry(e) -> ModifiedEntry.encode encode e
;;

let kind (comp: t) (entry: entry) (rest: entry list) =
  let (theDeepestCompChildOpt, theDeepestCompOpt) =
    Belt.List.reduce
      rest
      (None, None)
      (fun (prev, found) curr ->
        match found with
        | Some _ -> (prev, found)
        | None -> (
          match curr with
          | Entry _ -> (Some curr, None)
          | ModifiedEntry modifiedEntry -> (
              prev,
              Some modifiedEntry.children
            )
        )
      )
  in let theDeepestComp = theDeepestCompOpt |> (Utils.defaultTo comp)
  and theDeepestCompChild = theDeepestCompChildOpt |> (Utils.defaultTo entry)
  in (
    match theDeepestCompChild with
    | Entry entry -> Rationale.Option.Infix.(
      let findEntry entry = List.find_opt (fun e -> e == entry)
      in let added = theDeepestComp.added |> findEntry entry <$> (fun _ -> CompareKind.Added)
      and removed = theDeepestComp.removed |> findEntry entry <$> (fun _ -> CompareKind.Removed)
      and intact = theDeepestComp.intact |> findEntry entry <$> (fun _ -> CompareKind.Intact)
      in added |? removed |? intact
    )
    | ModifiedEntry _ -> Some CompareKind.Modified
  ) |> Utils.defaultTo CompareKind.Intact
;;

type data =
  | EntryData of Entry.Data.t
  | ModifiedEntryData of ModifiedEntry.Data.t
;;

type children =
  | ModifiedChildren of t
  | NotModifiedChildren of Entry.t list
;;

module OveralSize = struct
  let getSize (entry: Entry.t) = match (entry.parsed, entry.stat) with
    | (Some { size }, _) -> size
    | (None, Some { size }) -> size
    | _ -> 0
  ;;

  let calcSize = Rationale.Function.Infix.(List.map getSize ||> List.fold_left (+) 0);;

  let make (a : Entry.t list) (b : Entry.t list) = (a |> calcSize, b |> calcSize);;

  let encode = Json.Encode.(tuple2 int int);;
end