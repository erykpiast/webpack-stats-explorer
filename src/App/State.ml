module NavigationPath = struct
  module Segment = struct
    type t = CompareEntry.entry * CompareKind.t;;
    let make (kind : CompareKind.t) item = (item, kind);;

    let encode r =
      let encodedEntry = CompareEntry.(
        match (r |> fst) with
        | Entry(entry) -> Entry.encode entry
        | ModifiedEntry(modifiedEntry) -> ModifiedEntry.encode CompareEntry.encode modifiedEntry
      )
      and encodedKind = r |> snd |> CompareKind.encode
      in Json.Encode.jsonArray [|encodedEntry; encodedKind|]
    ;;
  end

  type t = Segment.t list;;

  let encode = Json.Encode.list Segment.encode;;
end

type compare = CompareEntry.t;;

type t =
  { index : int
  ; stats : WebpackStats.t list
  ; navigationPath : NavigationPath.t
  ; isTimelineVisible : bool
  ; urls : string list
  }
;;
