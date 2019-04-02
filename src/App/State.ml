

module NavigationPath = struct
  module Segment = struct
    module Item = struct
      type t =
        | Chunk of Compare.Chunks.chunk
        | Module of Compare.Modules.module_;;
    end

    type t = (Item.t * Compare.Kind.t);;

    let of_chunk (kind: Compare.Kind.t) item = (Item.Chunk item, kind);;
    let of_module (kind: Compare.Kind.t) item = (Item.Module item, kind);;
  end

  type t = Segment.t list;;
end

type t = {
  index: int;
  comparisons: Compare.t list;
  navigationPath: NavigationPath.t;
};;