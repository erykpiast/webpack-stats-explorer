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

  let convertToSourceTree path =
    match (path |> List.rev) with
    | [] -> []
    | chunkSegment::[] -> [chunkSegment]
    | (lastSegment, kind)::_ ->
      let chunkSegment = path |> List.hd
      in lastSegment
        |> SourceTree.parsePath
        |> List.map (fun segment -> (segment, kind))
        |> Utils.List.prepend chunkSegment
  ;;

  (**
    * TODO: implement it
    * it's impossible to derive Webpack Tree path from Source Tree one
    * most probably it'd be necessary to keep original ID
    * or even the whole path in mapped entry
    *)
  let convertFromSourceTree path = path;;
end

type compare = CompareEntry.t;;

type t =
  { index : int
  ; tab : int
  ; stats : WebpackStats.t list
  ; navigationPath : NavigationPath.t
  ; isTimelineVisible : bool
  ; urls : string list
  ; sourceTree : bool
  }
;;
