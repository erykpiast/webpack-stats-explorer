type t =
  { assets : string list
  ; built : bool
  ; cacheable : bool
  ; chunks : string list
  ; depth : int
  ; errors : int
  ; failed : bool
  ; id : string option
  ; identifier : string
  ; index : int option
  ; index2 : int option
  ; issuer : string option
  ; issuerId : string option
  ; issuerName : string option
  ; issuerPath : string list option
  ; modules : t list option
  ; name : string
  ; optimizationBailout : string list
  ; optional : bool
  ; prefetched : bool
  ; profile : WebpackProfile.t option
  ; providedExports : string list option
  ; reasons : WebpackReason.t list
  ; size : int
  ; ownSize : int
  ; source : string option
  ; originalSize : int option
  ; originalSource : string option
  ; parsedSize : int option
  ; parsedSource : string option
  ; usedExports : bool option
  ; warnings : int
  }
;;

let rec decode json =
  Json.Decode.
    { assets = json |> field "assets" (list string)
    ; built = json |> field "built" bool
    ; cacheable = json |> optional (field "cacheable" bool) |> Utils.defaultTo(false)
    ; chunks = json |> field "chunks" (list Utils.Json.Decode.forceString)
    ; depth = json |> field "depth" int
    ; errors = json |> field "errors" int
    ; failed = json |> field "failed" bool
    ; id = json |> field "id" (optional Utils.Json.Decode.forceString)
    ; identifier = json |> field "identifier" string
    ; index = json |> field "index" (optional int)
    ; index2 = json |> field "index2" (optional int)
    ; issuer = json |> field "issuer" (optional string)
    ; issuerId = json |> field "issuerId" (optional string)
    ; issuerName = json |> field "issuerName" (optional string)
    ; issuerPath = json |> field "issuerPath" (optional (list string))
    ; modules = json |> optional (field "modules" (list decode))
    ; name = json |> field "name" string
    ; optimizationBailout = json |> field "optimizationBailout" (list string)
    ; optional = json |> field "optional" bool
    ; prefetched = json |> field "prefetched" bool
    ; profile = json |> optional (field "profile" WebpackProfile.decode)
    ; providedExports = json |> field "providedExports" (optional (list string))
    ; reasons = json |> field "reasons" (list WebpackReason.decode)
    ; size = json |> field "size" int
    ; ownSize = json |> field "size" int
    ; source = json |> optional (field "source" string)
    ; originalSize = json |> optional (field "originalSize" int)
    ; originalSource = json |> optional (field "originalSource" string)
    ; parsedSize = json |> optional (field "parsedSize" int)
    ; parsedSource = json |> optional (field "parsedSource" string)
    ; usedExports = json |> optional (field "usedExports" bool)
    ; warnings = json |> field "warnings" int
    }
;;

let rec encode r =
  Json.Encode.(
    object_
      [ "assets", r.assets |> list string
      ; "built", r.built |> bool
      ; "cacheable", r.cacheable |> bool
      ; "chunks", r.chunks |> list string
      ; "depth", r.depth |> int
      ; "errors", r.errors |> int
      ; "failed", r.failed |> bool
      ; "id", r.id |> nullable string
      ; "identifier", r.identifier |> string
      ; "index", r.index |> nullable int
      ; "index2", r.index2 |> nullable int
      ; "issuer", r.issuer |> nullable string
      ; "issuerId", r.issuerId |> nullable string
      ; "issuerName", r.issuerName |> nullable string
      ; "issuerPath", r.issuerPath |> nullable (list string)
      ; "modules", r.modules |> nullable (list encode)
      ; "name", r.name |> string
      ; "optimizationBailout", r.optimizationBailout |> list string
      ; "optional", r.optional |> bool
      ; "prefetched", r.prefetched |> bool
      ; "profile", r.profile |> nullable WebpackProfile.encode
      ; "providedExports", r.providedExports |> nullable (list string)
      ; "reasons", r.reasons |> list WebpackReason.encode
      ; "size", r.size |> int
      ; "ownSize", r.ownSize |> int
      ; "source", r.source |> nullable string
      ; "originalSize", r.originalSize |> nullable int
      ; "originalSource", r.originalSource |> nullable string
      ; "parsedSize", r.parsedSize |> nullable int
      ; "parsedSource", r.parsedSource |> nullable string
      ; "usedExports", r.usedExports |> nullable bool
      ; "warnings", r.warnings |> int
      ])
;;

let make
    assets
    built
    cacheable
    chunks
    depth
    errors
    failed
    id
    identifier
    index
    index2
    issuer
    issuerId
    issuerName
    issuerPath
    modules
    name
    optimizationBailout
    optional
    prefetched
    profile
    providedExports
    reasons
    size
    ownSize
    source
    originalSize
    originalSource
    parsedSize
    parsedSource
    usedExports
    warnings
  =
  { assets
  ; built
  ; cacheable
  ; chunks
  ; depth
  ; errors
  ; failed
  ; id
  ; identifier
  ; index
  ; index2
  ; issuer
  ; issuerId
  ; issuerName
  ; issuerPath
  ; modules
  ; name
  ; optimizationBailout
  ; optional
  ; prefetched
  ; profile
  ; providedExports
  ; reasons
  ; size
  ; ownSize
  ; source
  ; originalSize
  ; originalSource
  ; parsedSize
  ; parsedSource
  ; usedExports
  ; warnings
  }
;;

let isEntryPoint module_ = match module_.reasons with
  | [reason] -> reason.module_ = None
  | _ -> false
;;

let hasSubmodules module_ = match module_.modules with
  | None -> false
  | Some(modules) -> List.length modules > 0
;;

let hasCode module_ = match module_.source with
  | None -> false
  | Some(_) -> true
;;
