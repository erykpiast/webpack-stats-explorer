open Rationale.Option.Infix;;

module Segment = struct
  type t = CompareEntry.entry;;

  let make entry = entry;;

  let encode = CompareEntry.encodeEntry;;

  let findEntryById id = Utils.List.findOpt (Entry.hasId id);;

  let findModifiedEntryById id = Utils.List.findOpt (ModifiedEntry.hasId id);;

  let fromEntries id (entries : Entry.t list) =
    entries |> findEntryById id <$> (fun entry -> CompareEntry.Entry(entry))
  ;;

  let fromCompareEntry id (comp : CompareEntry.t) =
    let addedEntry = comp.added |> fromEntries id
    and removedEntry = comp.removed |> fromEntries id
    and intactEntry = comp.intact |> fromEntries id
    and modifiedEntry = comp.modified
      |> (findModifiedEntryById id)
      <$> (fun entry -> CompareEntry.ModifiedEntry(entry))
    in addedEntry |? removedEntry |? intactEntry |? modifiedEntry
  ;;

  let toState entry = State.NavigationPath.Segment.make entry;;
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
        match segment with
        | Entry entry -> segment::(fromState (NotModifiedChildren entry.children) rest)
        | ModifiedEntry entry -> segment::(fromState (ModifiedChildren entry.children) rest)
      )
    )
  )
;;
