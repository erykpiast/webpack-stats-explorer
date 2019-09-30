module NavigationPath = struct
  module Segment = struct
    module Item = struct
      type t =
        | Chunk of Compare.Chunks.chunk
        | Module of Compare.Modules.module_
        | Entry of CompareEntry.entry
    end

    type t = Item.t * CompareKind.t

    let of_chunk (kind : CompareKind.t) item = Item.Chunk item, kind
    let of_module (kind : CompareKind.t) item = Item.Module item, kind
    let of_entry (kind : CompareKind.t) item = Item.Entry item, kind
  end

  type t = Segment.t list
end

type compare =
  | Legacy of Compare.t
  | Entry of CompareEntry.t
;;

type t =
  { index : int
  ; comparisons : compare list
  ; navigationPath : NavigationPath.t
  }
;;
