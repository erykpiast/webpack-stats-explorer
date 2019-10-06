module Modules = struct
  module Summary = struct
    type t =
      { name : string
      ; size : int
      ; ownSize : int
      ; source : string
      ; modules : t list
      }

    let rec make (m : Module.t) =
      { name = m.name
      ; size = m.size
      ; ownSize = m.ownSize
      ; source = m.source |> Utils.defaultTo ""
      ; modules = m.modules |> Utils.defaultTo [] |> List.map make
      }
    ;;

    let rec encode r =
      Json.Encode.(
        object_
          [ "name", r.name |> string
          ; "size", r.size |> int
          ; "ownSize", r.ownSize |> int
          ; "source", r.source |> string
          ; "modules", r.modules |> list encode
          ])
    ;;
  end

  module ModifiedSummary = struct
    type 'diff t =
      { name : string
      ; size : int * int
      ; ownSize : int * int
      ; source : string * string
      ; modules : 'diff option
      }

    let make diff (a : Module.t) (b : Module.t) =
      { name = b.name
      ; size = a.size, b.size
      ; ownSize = a.ownSize, b.ownSize
      ; source = a.source |> Utils.defaultTo "", b.source |> Utils.defaultTo ""
      ; modules =
          (match a.modules, b.modules with
          | None, None -> None
          | ams, bms ->
            Some (diff (ams |> Utils.defaultTo []) (bms |> Utils.defaultTo [])))
      }
    ;;

    let encode diff r =
      Json.Encode.(
        object_
          [ "name", r.name |> string
          ; "size", r.size |> tuple2 int int
          ; "ownSize", r.ownSize |> tuple2 int int
          ; "source", r.source |> tuple2 string string
          ; "modules", r.modules |> nullable diff
          ])
    ;;
  end

  type t =
    { added : Summary.t list
    ; removed : Summary.t list
    ; intact : Summary.t list
    ; modified : t ModifiedSummary.t list
    }

  type module_ =
    | Summary of Summary.t
    | ModifiedSummary of t ModifiedSummary.t

  type modules =
    | ModifiedModules of t
    | NotModifiedModules of Summary.t list

  let nameEqual (a : Module.t) (b : Module.t) = a.name = b.name
  let builtEqual (a : Module.t) (b : Module.t) = a.built = b.built
  let similar = Utils.Function.(allPass [
    uncurry2 nameEqual;
    uncurry2 builtEqual
  ] |> curry2)
  let diffModules = Diff.create similar Module.eql

  let normalize = Rationale.Function.Infix.(
    List.map (fun (module_: Module.t) -> match module_.modules with
    | None -> module_
    | Some modules -> match Utils.List.findOpt (nameEqual module_) modules with
      | None -> module_
      | Some mainSubmodule -> { module_ with source = mainSubmodule.source
      ; modules = Some(List.filter ((!=) mainSubmodule) modules)
      ; ownSize = mainSubmodule.size
      }
    )
    ||> List.filter (fun (module_: Module.t) ->
      module_.built &&
      (
        module_ |> Module.hasCode
        || module_ |> Module.hasSubmodules
        || module_ |> Module.isEntryPoint |> not
      )
    )
  );;

  let rec make xs ys =
    let d = diffModules (normalize xs) (normalize ys) in
    { added = d.added |> List.map Summary.make
    ; removed = d.removed |> List.map Summary.make
    ; intact = d.intact |> List.map Summary.make
    ; modified = d.modified |> List.map (fun (a, b) -> ModifiedSummary.make make a b)
    }
  ;;

  let rec encode r =
    Json.Encode.(
      object_
        [ "added", r.added |> list Summary.encode
        ; "removed", r.removed |> list Summary.encode
        ; "intact", r.intact |> list Summary.encode
        ; "modified", r.modified |> list (ModifiedSummary.encode encode)
        ])
  ;;

  let count diff =
    let sum = List.fold_left (+) 0
    in (
      [
        diff.intact |> List.length;
        diff.removed |> List.length;
        diff.modified |> List.length
      ] |> sum,
      [
        diff.intact |> List.length;
        diff.added |> List.length;
        diff.modified |> List.length
      ] |> sum
    )
  ;;
end

module Chunks = struct

  let getFilename (ch : Chunk.t) =
    Utils.List.findOpt (Js.String.endsWith ".js") ch.files
    |> Utils.defaultTo (List.nth ch.files 0)
  ;;

  let getName (ch : Chunk.t) =
    match ch.names with
    | [] -> getFilename ch
    | name :: _ -> name
  ;;

  module Summary = struct
    type t =
      { name : string
      ; filename : string
      ; size : int
      ; modules : Modules.Summary.t list
      }

    let make (ch : Chunk.t) =
      { name = getName ch
      ; filename = getFilename ch
      ; size = ch.size
      ; modules = ch.modules |> List.map Modules.Summary.make
      }
    ;;

    let encode r =
      Json.Encode.(
        object_
          [ "name", r.name |> string
          ; "filename", r.filename |> string
          ; "size", r.size |> int
          ; "modules", r.modules |> list Modules.Summary.encode
          ])
    ;;
  end

  module ModifiedSummary = struct
    type t =
      { name : string
      ; filename : string * string
      ; size : int * int
      ; modules : Modules.t
      }

    let make (a : Chunk.t) (b : Chunk.t) =
      { name = getName a
      ; filename = getName a, getName b
      ; size = a.size, b.size
      ; modules = Modules.make a.modules b.modules
      }
    ;;

    let encode r =
      Json.Encode.(
        object_
          [ "name", r.name |> string
          ; "filename", r.filename |> tuple2 string string
          ; "size", r.size |> tuple2 int int
          ; "modules", r.modules |> Modules.encode
          ])
    ;;
  end

  type t =
    { added : Summary.t list
    ; removed : Summary.t list
    ; intact : Summary.t list
    ; modified : ModifiedSummary.t list
    }

  type chunk =
    | Summary of Summary.t
    | ModifiedSummary of ModifiedSummary.t

  let hashPattern = [%re "/\\/?(.*)(?:\\.[0-9a-f]+)(?:\\.chunk)?(\\.js|\\.css)/"]

  let removeHash filename =
    let separator = "/" in
    let split = Js.String.split separator filename
      |> Array.to_list
      |> List.rev
    in match split with
    | hd :: tl -> (
        Js.String.unsafeReplaceBy2
        hashPattern
        (fun _ p1 p2 _ _ -> p1 ^ p2)
        hd
      )::tl
      |> List.rev
      |> Array.of_list
      |> Js.Array.joinWith separator
    | [] -> filename

  let similar (a : Chunk.t) (b : Chunk.t) =
    Utils.List.isEqual
      (List.map removeHash a.files)
      (List.map removeHash b.files)
      ()
    || (List.length a.names != 0 && Utils.List.isEqual a.names b.names ())
  ;;

  let diffChunks = Diff.create similar Chunk.eql

  let make xs ys =
    let d = diffChunks xs ys in
    { added = d.added |> List.map Summary.make
    ; removed = d.removed |> List.map Summary.make
    ; intact = d.intact |> List.map Summary.make
    ; modified = d.modified |> List.map (fun (a, b) -> ModifiedSummary.make a b)
    }
  ;;

  let encode r =
    Json.Encode.(
      object_
        [ "added", r.added |> list Summary.encode
        ; "removed", r.removed |> list Summary.encode
        ; "intact", r.intact |> list Summary.encode
        ; "modified", r.modified |> list ModifiedSummary.encode
        ])
  ;;
end

module Kind = struct
  type t =
    | Added
    | Intact
    | Modified
    | Removed
end

type t =
  { chunks : Chunks.t
  ; size : int * int
  ;count : int
  }

let calcSize = List.fold_left (fun acc (a : Chunk.t) -> a.size + acc) 0

let make (a : Stats.t) (b : Stats.t) =
  { chunks = Chunks.make a.chunks b.chunks; size = calcSize a.chunks, calcSize b.chunks; count = List.length b.chunks }
;;

let encode r =
  Json.Encode.(
    object_ [ "chunks", r.chunks |> Chunks.encode; "size", r.size |> tuple2 int int ])
;;