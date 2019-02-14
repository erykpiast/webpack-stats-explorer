module Modules = struct
  module Summary = struct
    type t = {
      name    : string;
      size    : int;
      source  : string;
      modules : t list;
    };;

    let rec make (m: Module.t) = {
      name    = m.name;
      size    = m.size;
      source  = m.source  |> Utils.defaultTo "";
      modules = m.modules |> Utils.defaultTo [] |> List.map make
    };;

    let rec encode r = Json.Encode.(object_ [
      ("name",    r.name    |> string);
      ("size",    r.size    |> int);
      ("source",  r.source  |> string);
      ("modules", r.modules |> list encode);
    ]);;
  end

  module ModifiedSummary = struct
    type 'diff t = {
      name    : string;
      size    : int * int;
      source  : string * string;
      modules : 'diff option;
    };;

    let make diff (a: Module.t) (b: Module.t) = {
      name    = b.name;
      size    = (a.size, b.size);
      source  = (
        a.source |> Utils.defaultTo "",
        b.source |> Utils.defaultTo ""
      );
      modules = (match (a.modules, b.modules) with
      | (None, None) -> None
      | (ams, bms) -> Some (diff
        (ams |> Utils.defaultTo [])
        (bms |> Utils.defaultTo []));
      )
    };;

    let encode diff r = Json.Encode.(object_ [
      ("name",    r.name    |> string);
      ("size",    r.size    |> tuple2 int int);
      ("source",  r.source  |> tuple2 string string);
      ("modules", r.modules |> nullable diff);
    ]);;
  end

  type t = {
    added     : Summary.t list;
    removed   : Summary.t list;
    intact    : Summary.t list;
    modified  : t ModifiedSummary.t list;
  };;

  let similar (a: Module.t) (b: Module.t) = a.name = b.name;;
  let diffModules = Diff.create similar Module.eql;;
  let rec make xs ys =
    let d = diffModules xs ys
    in {
      added    = d.added    |> List.map Summary.make;
      removed  = d.removed  |> List.map Summary.make;
      intact   = d.intact   |> List.map Summary.make;
      modified = d.modified |> List.map (fun (a, b) -> ModifiedSummary.make make a b);
    };;

  let rec encode r = Json.Encode.(object_ [
    ("added",    r.added    |> list Summary.encode);
    ("removed",  r.removed  |> list Summary.encode);
    ("intact",   r.intact   |> list Summary.encode);
    ("modified", r.modified |> list (ModifiedSummary.encode encode));
  ]);;
end

module Chunks = struct

  let getName (ch: Chunk.t) = (match ch.names with
  | [] -> List.nth ch.files 0
  | name::_ -> name
  );;

  let getFilename (ch: Chunk.t) = List.nth ch.files 0;;

  module Summary = struct
    type t = {
      name     : string;
      filename : string;
      size     : int;
      modules  : Modules.Summary.t list;
    };;

    let make (ch: Chunk.t) = {
      name     = getName ch;
      filename = getFilename ch;
      size     = ch.size;
      modules  = ch.modules |> List.map Modules.Summary.make
    };;

    let encode r = Json.Encode.(object_ [
      ("name",     r.name      |> string);
      ("filename", r.filename  |> string);
      ("size",     r.size      |> int);
      ("modules",  r.modules   |> list Modules.Summary.encode);
    ]);;
  end

  module ModifiedSummary = struct
    type t = {
      name     : string;
      filename : string * string;
      size     : int * int;
      modules  : Modules.t;
    };;

    let make diff (a: Chunk.t) (b: Chunk.t) = {
      name     = getName a;
      filename = (getName a, getName b);
      size     = (a.size, b.size);
      modules  = Modules.make a.modules b.modules
    };;

    let encode r = Json.Encode.(object_ [
      ("name",     r.name      |> string);
      ("filename", r.filename  |> tuple2 string string);
      ("size",     r.size      |> tuple2 int int);
      ("modules",  r.modules   |> Modules.encode);
    ]);;
  end

  type chunk =
    | Summary of Summary.t
    | ModifiedSummary of ModifiedSummary.t;;

  type t = {
    added     : Summary.t list;
    removed   : Summary.t list;
    intact    : Summary.t list;
    modified  : ModifiedSummary.t list;
  };;

  let similar (a: Chunk.t) (b: Chunk.t) =
    (Utils.List.isEqual a.files b.files) ||
    ((Utils.List.isEqual a.names b.names) && ((List.length a.names) != 0))
  ;;
  let diffChunks = Diff.create similar Chunk.eql;;
  let rec make xs ys =
    let d = diffChunks xs ys
    in {
      added    = d.added    |> List.map Summary.make;
      removed  = d.removed  |> List.map Summary.make;
      intact   = d.intact   |> List.map Summary.make;
      modified = d.modified |> List.map (fun (a, b) -> ModifiedSummary.make make a b);
    };;

  let rec encode r = Json.Encode.(object_ [
    ("added",    r.added    |> list Summary.encode);
    ("removed",  r.removed  |> list Summary.encode);
    ("intact",   r.intact   |> list Summary.encode);
    ("modified", r.modified |> list ModifiedSummary.encode);
  ]);;
end

type t = {
  chunks  : Chunks.t;
  size    : int * int;
};;

let calcSize = List.fold_left (fun acc (a: Chunk.t) -> a.size + acc) 0;;

let make (a : Stats.t) (b : Stats.t) = {
  chunks = Chunks.make a.chunks b.chunks;
  size   = (calcSize a.chunks, calcSize b.chunks);
};;

let encode r = Json.Encode.(object_ [
  ("chunks", r.chunks |> Chunks.encode);
  ("size",   r.size   |> tuple2 int int);
]);;