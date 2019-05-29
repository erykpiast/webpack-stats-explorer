type t =
  { loc : string
  ; module_ : string
  ; moduleIdentifier : string
  ; moduleName : string
  ; reasons : Reason.t list
  ; request : string option
  }

let decode json =
  Json.Decode.
    { loc = json |> field "loc" string
    ; module_ = json |> field "module" string
    ; moduleIdentifier = json |> field "moduleIdentifier" string
    ; moduleName = json |> field "moduleName" string
    ; reasons = json |> field "reasons" (list Reason.decode)
    ; request = json |> field "request" (optional string)
    }
;;

let encode r =
  Json.Encode.(
    object_
      [ "loc", r.loc |> string
      ; "module", r.module_ |> string
      ; "moduleIdentifier", r.moduleIdentifier |> string
      ; "moduleName", r.moduleName |> string
      ; "reasons", r.reasons |> list Reason.encode
      ; "request", r.request |> nullable string
      ])
;;
