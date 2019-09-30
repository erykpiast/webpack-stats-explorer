let both a b = match (a, b) with
  | (Some(aSize), Some(bSize)) -> Some(aSize, bSize)
  | _ -> None
;;

module Modules = struct
  module Summary = struct
    type t =
      { name : string
      ; size : int
      ; ownSize : int
      ; originalSize : int option
      ; parsedSize : int option
      ; source : string
      ; originalSource : string option
      ; parsedSource : string option
      ; modules : t list
      }

    let rec make (m : WebpackModule.t) =
      { name = m.name
      ; size = m.size
      ; ownSize = m.ownSize
      ; originalSize = m.originalSize
      ; parsedSize = m.parsedSize
      ; source = m.source |> Utils.defaultTo ""
      ; originalSource = m.originalSource
      ; parsedSource = m.parsedSource
      ; modules = m.modules |> Utils.defaultTo [] |> List.map make
      }
    ;;

    let rec encode r =
      Json.Encode.(
        object_
          [ "name", r.name |> string
          ; "size", r.size |> int
          ; "ownSize", r.ownSize |> int
          ; "originalSize", r.originalSize |> nullable int
          ; "parsedSize", r.parsedSize |> nullable int
          ; "source", r.source |> string
          ; "originalSource", r.originalSource |> nullable string
          ; "parsedSource", r.parsedSource |> nullable string
          ; "modules", r.modules |> list encode
          ])
    ;;
  end

  module ModifiedSummary = struct
    type 'diff t =
      { name : string
      ; size : int * int
      ; ownSize : int * int
      ; originalSize : (int * int) option
      ; parsedSize : (int * int) option
      ; source : string * string
      ; originalSource : (string * string) option
      ; parsedSource : (string * string) option
      ; modules : 'diff option
      }

    let make diff (a : WebpackModule.t) (b : WebpackModule.t) =
      { name = b.name
      ; size = a.size, b.size
      ; ownSize = a.ownSize, b.ownSize
      ; originalSize = both a.originalSize b.originalSize
      ; parsedSize = both a.parsedSize b.parsedSize
      ; source = a.source |> Utils.defaultTo "", b.source |> Utils.defaultTo ""
      ; originalSource = both a.originalSource b.originalSource
      ; parsedSource = both a.parsedSource b.parsedSource
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
          ; "originalSize", r.originalSize |> nullable (tuple2 int int)
          ; "parsedSize", r.parsedSize |> nullable (tuple2 int int)
          ; "source", r.source |> tuple2 string string
          ; "originalSource", r.originalSource |> nullable (tuple2 string string)
          ; "parsedSource", r.parsedSource |> nullable (tuple2 string string)
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

  let nameEqual (a : WebpackModule.t) (b : WebpackModule.t) = a.name = b.name
  let builtEqual (a : WebpackModule.t) (b : WebpackModule.t) = a.built = b.built
  let similar = Utils.Function.(allPass [
    uncurry2 nameEqual;
    uncurry2 builtEqual
  ] |> curry2)
  let diffModules = Diff.create similar WebpackModule.eql

  let normalize = Rationale.Function.Infix.(
    List.map (fun (module_: WebpackModule.t) -> match module_.modules with
    | None -> module_
    | Some modules -> match Utils.List.findOpt (nameEqual module_) modules with
      | None -> module_
      | Some mainSubmodule -> { module_ with source = mainSubmodule.source
      ; modules = Some(List.filter ((!=) mainSubmodule) modules)
      ; ownSize = mainSubmodule.size
      }
    )
    ||> List.filter (fun (module_: WebpackModule.t) ->
      module_.built &&
      (
        module_ |> WebpackModule.hasCode
        || module_ |> WebpackModule.hasSubmodules
        || module_ |> WebpackModule.isEntryPoint |> not
      )
    )
  );;

  let rec make xs ys =
    let d = diffModules xs ys in
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

  let getFilename (ch : WebpackChunk.t) =
    Utils.List.findOpt (Js.String.endsWith ".js") ch.files
    |> Utils.defaultTo (List.nth ch.files 0)
  ;;

  let getName (ch : WebpackChunk.t) =
    match ch.names with
    | [] -> getFilename ch
    | name :: _ -> name
  ;;

  module Summary = struct
    type t =
      { name : string
      ; filename : string
      ; size : int
      ; parsedSize : int option
      ; modules : Modules.Summary.t list
      }

    let make (ch : WebpackChunk.t) =
      { name = getName ch
      ; filename = getFilename ch
      ; size = ch.size
      ; parsedSize = ch.parsedSize
      ; modules = ch.modules |> List.map Modules.Summary.make
      }
    ;;

    let encode r =
      Json.Encode.(
        object_
          [ "name", r.name |> string
          ; "filename", r.filename |> string
          ; "size", r.size |> int
          ; "parsedSize", r.parsedSize |> nullable int
          ; "modules", r.modules |> list Modules.Summary.encode
          ])
    ;;
  end

  module ModifiedSummary = struct
    type t =
      { name : string
      ; filename : string * string
      ; size : int * int
      ; parsedSize : (int * int) option
      ; modules : Modules.t
      }

    let make (a : WebpackChunk.t) (b : WebpackChunk.t) =
      { name = getName a
      ; filename = getName a, getName b
      ; size = a.size, b.size
      ; parsedSize = both a.parsedSize b.parsedSize
      ; modules = Modules.make a.modules b.modules
      }
    ;;

    let encode r =
      Json.Encode.(
        object_
          [ "name", r.name |> string
          ; "filename", r.filename |> tuple2 string string
          ; "size", r.size |> tuple2 int int
          ; "parsedSize", r.parsedSize |> nullable (tuple2 int int)
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

  let similar (a : WebpackChunk.t) (b : WebpackChunk.t) =
    Utils.List.isEqual
      (List.map removeHash a.files)
      (List.map removeHash b.files)
      ()
    || (List.length a.names != 0 && Utils.List.isEqual a.names b.names ())
  ;;

  let diffChunks = Diff.create similar WebpackChunk.eql

  let nameEqual (a : WebpackModule.t) (b : WebpackModule.t) = a.name = b.name

  let normalize =
    List.map (fun (chunk: WebpackChunk.t) ->
      let normalizedModules = Modules.normalize chunk.modules in
      let parsedSize = normalizedModules
        |> List.map (fun (module_: WebpackModule.t) -> module_.parsedSize |> (Utils.defaultTo 0))
        |> List.fold_left (+) 0
      in { chunk with parsedSize = Some(parsedSize)
         ; modules = normalizedModules
      });;

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

type t =
  { chunks : Chunks.t
  ; size : int * int
  ; count : int
  }

let calcSize = List.fold_left (fun acc (a : WebpackChunk.t) ->
  let size =
    match (a.parsedSize) with
    | Some(size) -> size
    | None -> a.size
  in size + acc) 0

let make (a : WebpackStats.t) (b : WebpackStats.t) =
  let aChunks = Chunks.normalize a.chunks
  and bChunks = Chunks.normalize b.chunks
  in { chunks = Chunks.make aChunks bChunks
     ; size = calcSize aChunks, calcSize bChunks
     ; count = List.length bChunks
  }
;;

let encode r =
  Json.Encode.(
    object_ [ "chunks", r.chunks |> Chunks.encode; "size", r.size |> tuple2 int int ])
;;
