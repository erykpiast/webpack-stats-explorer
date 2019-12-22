type t =
  { childrenByOrder : string Js.Dict.t
  ; entry : bool
  ; files : string list
  ; filteredModules : int
  ; hash : string
  ; id : string
  ; initial : bool
  ; modules : WebpackModule.t list
  ; names : string list
  ; origins : WebpackOrigin.t list
  ; parents : int list
  ; rendered : bool
  ; siblings : int list
  ; size : int
  ; parsedSize : int option
  }

let decode json =
  Json.Decode.
    { childrenByOrder = json |> field "childrenByOrder" (dict string)
    ; entry = json |> field "entry" bool
    ; files = json |> field "files" (list string)
    ; filteredModules = json |> field "filteredModules" int
    ; hash = json |> field "hash" string
    ; id = json |> field "id" Utils.Json.Decode.forceString
    ; initial = json |> field "initial" bool
    ; modules = json |> field "modules" (list WebpackModule.decode)
    ; names = json |> field "names" (list string)
    ; origins = json |> field "origins" (list WebpackOrigin.decode)
    ; parents = json |> field "parents" (list int)
    ; rendered = json |> field "rendered" bool
    ; siblings = json |> field "siblings" (list int)
    ; size = json |> field "size" int
    ; parsedSize = json |> optional (field "size" int)
    }
;;

let encode r =
  Json.Encode.(
    object_
      [ "childrenByOrder", r.childrenByOrder |> dict string
      ; "entry", r.entry |> bool
      ; "files", r.files |> list string
      ; "filteredModules", r.filteredModules |> int
      ; "hash", r.hash |> string
      ; "id", r.id |> string
      ; "initial", r.initial |> bool
      ; "modules", r.modules |> list WebpackModule.encode
      ; "names", r.names |> list string
      ; "origins", r.origins |> list WebpackOrigin.encode
      ; "parents", r.parents |> list int
      ; "rendered", r.rendered |> bool
      ; "siblings", r.siblings |> list int
      ; "size", r.size |> int
      ; "parsedSize", r.parsedSize |> nullable int
      ])
;;

let make
    childrenByOrder
    entry
    files
    filteredModules
    hash
    id
    initial
    modules
    names
    origins
    parents
    rendered
    siblings
    size
    parsedSize
  =
  { childrenByOrder
  ; entry
  ; files
  ; filteredModules
  ; hash
  ; id
  ; initial
  ; modules
  ; names
  ; origins
  ; parents
  ; rendered
  ; siblings
  ; size
  ; parsedSize
  }
;;

let eql a b =
  a.size = b.size
  && Utils.List.isEqual a.names b.names ()
  && Utils.List.isEqual a.files b.files ()
  && Utils.List.isEqual a.modules b.modules ~eql:WebpackModule.eql ()
;;
