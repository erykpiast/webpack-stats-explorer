module Segment = struct
  type t =
    | Root
    | Directory of string
    | File of string
  ;;

  let make =
    function
    | (".", true) -> Root
    | (name, false) -> Directory name
    | (name, true) -> File name
  ;;

  let toString =
    function
    | Root -> "."
    | Directory name -> name
    | File name -> name
  ;;
end

type t = Segment.t list;;

let make string : t =
  let segments = Utils.String.split "/" string
  in let segmentsCount = Array.length segments
  in let parsed = Array.mapi (fun index segment -> Segment.make (segment, index == segmentsCount)) segments
  in Array.to_list parsed
;;

let toString (path : t) = List.map Segment.toString path |> Array.of_list |> Utils.Array.join "/";;
