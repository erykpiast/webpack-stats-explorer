module ReasonPath = struct
    type t = Entry.t list;;
end

type t = ReasonPath.t list;;

let make (stats: WebpackStats.t) (entry: Entry.t) =
    []
;;