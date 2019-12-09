module Data = struct
  type t =
    { size : int * int
    ; source : string * string
    }
  ;;

  let make (a : Entry.Data.t option) (b : Entry.Data.t option) =
    match (a, b) with
    | (Some a, Some b) -> Some
      { size = (a.size, b.size)
      ; source = (a.source, b.source)
      }
    | _ -> None
  ;;

  let encode r =
    Json.Encode.(object_
      [ "size", r.size |> tuple2 int int
      ; "source", r.source |> tuple2 string string
      ]
    )
  ;;
end

type 'children t =
  { id : string
  ; size : int * int
  ; stat : Data.t option
  ; original : Data.t option
  ; parsed : Data.t option
  ; children : 'children
  }
;;

let make compareChildren (a : Entry.t) (b : Entry.t) =
  { id = a.id
  (* TODO: rethink what should be displayed as a size when one side misses the parsed one
    Showing (stat, parsed) may be misleading
  *)
  ; size = (a.size, b.size)
  ; stat = Data.make a.stat b.stat
  ; original = Data.make a.original b.original
  ; parsed = Data.make a.parsed b.parsed
  ; children = compareChildren a.children b.children
  }
;;

let encode encodeChildren r =
  Json.Encode.(object_
    [ "id", r.id |> string
    ; "size", r.size |> tuple2 int int
    ; "original", r.original |> nullable Data.encode
    ; "stat", r.stat |> nullable Data.encode
    ; "parsed", r.parsed |> nullable Data.encode
    ; "children", r.children |> encodeChildren
    ]
  )
;;

let hasId id entry =
  entry.id = id
;;
