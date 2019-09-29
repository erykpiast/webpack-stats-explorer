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

type entry =
  | Entry of Entry.t
  | ModifiedEntry of t ModifiedEntry.t
;;

type children =
  | ModifiedChildren of t
  | NotModifiedChildren of Entry.t list
;;

module Kind = struct
  type t =
    | Added
    | Intact
    | Modified
    | Removed
end

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