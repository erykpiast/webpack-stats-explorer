type t = {
  assets              : string list;
  built               : bool;
  cacheable           : bool;
  chunks              : int list;
  depth               : int;
  errors              : int;
  failed              : bool;
  id                  : int option;
  identifier          : string;
  index               : int;
  index2              : int;
  issuer              : string option;
  issuerId            : string option;
  issuerName          : string option;
  issuerPath          : string list option;
  modules             : t list option;
  name                : string;
  optimizationBailout : string list;
  optional            : bool;
  prefetched          : bool;
  profile             : Profile.t option;
  providedExports     : string list option;
  reasons             : Reason.t list;
  size                : int;
  source              : string option;
  usedExports         : bool option;
  warnings            : int;
};;

let rec decode json = Json.Decode.({
  assets              = (json |> field "assets" (list string));
  built               = (json |> field "built" bool);
  cacheable           = (json |> field "cacheable" bool);
  chunks              = (json |> field "chunks" (list int));
  depth               = (json |> field "depth" int);
  errors              = (json |> field "errors" int);
  failed              = (json |> field "failed" bool);
  id                  = (json |> field "id" (optional int));
  identifier          = (json |> field "identifier" string);
  index               = (json |> field "index" int);
  index2              = (json |> field "index2" int);
  issuer              = (json |> field "issuer" (optional string));
  issuerId            = (json |> field "issuerId" (optional string));
  issuerName          = (json |> field "issuerName" (optional string));
  issuerPath          = (json |> field "issuerPath" (optional (list string)));
  modules             = (json |> optional (field "modules" (list decode)));
  name                = (json |> field "name" string);
  optimizationBailout = (json |> field "optimizationBailout" (list string));
  optional            = (json |> field "optional" bool);
  prefetched          = (json |> field "prefetched" bool);
  profile             = (json |> optional (field "profile" Profile.decode));
  providedExports     = (json |> field "providedExports" (optional (list string)));
  reasons             = (json |> field "reasons" (list Reason.decode));
  size                = (json |> field "size" int);
  source              = (json |> optional (field "source" string));
  usedExports         = (json |> optional (field "usedExports" bool));
  warnings            = (json |> field "warnings" int);
});;

let rec encode r = Json.Encode.(object_ [
  ("assets",              r.assets |> list string);
  ("built",               r.built |> bool);
  ("cacheable",           r.cacheable |> bool);
  ("chunks",              r.chunks |> list int);
  ("depth",               r.depth |> int);
  ("errors",              r.errors |> int);
  ("failed",              r.failed |> bool);
  ("id",                  r.id |> nullable int);
  ("identifier",          r.identifier |> string);
  ("index",               r.index |> int);
  ("index2",              r.index2 |> int);
  ("issuer",              r.issuer |> nullable string);
  ("issuerId",            r.issuerId |> nullable string);
  ("issuerName",          r.issuerName |> nullable string);
  ("issuerPath",          r.issuerPath |> nullable (list string));
  ("modules",             r.modules |> nullable (list encode));
  ("name",                r.name |> string);
  ("optimizationBailout", r.optimizationBailout |> list string);
  ("optional",            r.optional |> bool);
  ("prefetched",          r.prefetched |> bool);
  ("profile",             r.profile |> nullable Profile.encode);
  ("providedExports",     r.providedExports |> nullable (list string));
  ("reasons",             r.reasons |> list Reason.encode);
  ("size",                r.size |> int);
  ("source",              r.source |> nullable string);
  ("usedExports",         r.usedExports |> nullable bool);
  ("warnings",            r.warnings |> int);
]);;

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
  source
  usedExports
  warnings
= {
  assets              = assets;
  built               = built;
  cacheable           = cacheable;
  chunks              = chunks;
  depth               = depth;
  errors              = errors;
  failed              = failed;
  id                  = id;
  identifier          = identifier;
  index               = index;
  index2              = index2;
  issuer              = issuer;
  issuerId            = issuerId;
  issuerName          = issuerName;
  issuerPath          = issuerPath;
  modules             = modules;
  name                = name;
  optimizationBailout = optimizationBailout;
  optional            = optional;
  prefetched          = prefetched;
  profile             = profile;
  providedExports     = providedExports;
  reasons             = reasons;
  size                = size;
  source              = source;
  usedExports         = usedExports;
  warnings            = warnings;
};;

let rec eql a b =
  (a.name = b.name) &&
  (a.size = b.size) &&
  (a.source = b.source) &&
  (match (a.modules, b.modules) with
    | (None, None) -> true
    | (None, Some(_)) -> false
    | (Some(_), None) -> false
    | (Some(ams), Some(bms)) ->
      (List.length(ams) = List.length(bms))
      && (List.fold_left2
        (fun acc a b -> acc && (eql a b))
        true
        ams
        bms)
  )
;;
