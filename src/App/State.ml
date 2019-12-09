module NavigationPath = struct
  module Segment = struct
    type t = string * CompareKind.t;;

    let make (kind : CompareKind.t) item = CompareEntry.(
      match (item) with
        | Entry(entry) -> (entry.id, kind)
        | ModifiedEntry(modifiedEntry) -> (modifiedEntry.id, kind)
    );;

    let encode (id, kind) =
      [|
        id;
        kind |> CompareKind.encode
      |] |> Json.Encode.jsonArray
    ;;

    let entryAndKindSeparator = "|";;

    let toString (id, kind) = id ^ entryAndKindSeparator ^ (kind |> CompareKind.toString);;

    let fromString entry =
      let parts = entry |> Utils.String.split entryAndKindSeparator |> Array.to_list
      in
        match (parts) with
        | id::kindString::[] ->
          let maybeKind = CompareKind.fromString kindString
          in (
            match (maybeKind) with
            | Some kind -> Some (id ^ "", kind)
            | None -> None
          )
        | _ -> None
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
