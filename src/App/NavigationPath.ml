open Rationale.Option.Infix;;

module Segment = struct
  type t = CompareEntry.entry * CompareKind.t;;

  let make (kind : CompareKind.t) entry = (entry, kind);;

  let encode = Json.Encode.tuple2 CompareEntry.encodeEntry CompareKind.encode;;

  let findEntryById id = Utils.List.findOpt (Entry.hasId id);;

  let findModifiedEntryById id = Utils.List.findOpt (ModifiedEntry.hasId id);;

  let fromEntries (id, kind) (entries : Entry.t list) =
    entries |> findEntryById id <$> (fun entry -> (CompareEntry.Entry(entry), kind))
  ;;

  let fromCompareEntry (id, kind) (comp : CompareEntry.t) = CompareKind.(
    match (kind) with
    | Added -> comp.added |> fromEntries (id, kind)
    | Removed -> comp.removed |> fromEntries (id, kind)
    | Intact -> comp.intact |> fromEntries (id, kind)
    | Modified -> comp.modified
      |> (findModifiedEntryById id)
      <$> (fun entry -> (CompareEntry.ModifiedEntry(entry), kind))
  );;

  let toState (entry, kind) = State.NavigationPath.Segment.make kind entry;;
end

type t = Segment.t list;;

let encode = Json.Encode.list Segment.encode;;

let rec fromState (comp : CompareEntry.children) (statePath : State.NavigationPath.t) =
  match (statePath) with
  | [] -> []
  | stateSegment::rest -> CompareEntry.(
    let maybeSegment = (
      match (comp) with
      | ModifiedChildren comparison -> Segment.fromCompareEntry stateSegment comparison
      | NotModifiedChildren entries -> Segment.fromEntries stateSegment entries
    ) in (
      match (maybeSegment) with
      | None -> []
      | Some segment -> (
        match (segment |> fst) with
        | Entry entry -> segment::(fromState (NotModifiedChildren entry.children) rest)
        | ModifiedEntry entry -> segment::(fromState (ModifiedChildren entry.children) rest)
      )
    )
  )
;;
