module NavigationPath = struct
  module Segment = struct
    type t = string;;

    let make item = CompareEntry.(
      match (item) with
        | Entry(entry) -> entry.id
        | ModifiedEntry(modifiedEntry) -> modifiedEntry.id
    );;

    let encode id = id |> Json.Encode.string;;

    let entryAndKindSeparator = "|";;

    let toString id = id;;

    let fromString id = id;;
  end

  type t = Segment.t list;;

  let encode = Json.Encode.list Segment.encode;;

  let convertToSourceTree path =
    match (path |> List.rev) with
    | [] -> []
    | chunkSegment::[] -> [chunkSegment]
    | lastSegment::_ ->
      let chunkSegment = path |> List.hd
      in lastSegment
        |> SourceTree.parsePath
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
