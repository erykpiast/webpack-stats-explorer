module NavigationPath = struct
  module Segment = struct
    type t = CompareEntry.entry * CompareKind.t
    let make (kind : CompareKind.t) item = (item, kind)
  end

  type t = Segment.t list
end

type compare = CompareEntry.t
;;

type t =
  { index : int
  ; comparisons : compare list
  ; navigationPath : NavigationPath.t
  }
;;
