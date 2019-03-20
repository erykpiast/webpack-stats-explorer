type activeItem =
  | Chunk of Compare.Chunks.chunk
  | Module of Compare.Modules.module_;;

module NavigationPath = struct
  type segment =
    | Added of activeItem
    | Removed of activeItem
    | Intact of activeItem
    | Modified of activeItem;;

  type t = segment list;;
end

type t = {
  index: int;
  comparisons: Compare.t list;
  navigationPath: NavigationPath.t;
};;