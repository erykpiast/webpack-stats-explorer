type t =
  { loc : string
  ; module_ : string
  ; moduleIdentifier : string
  ; moduleName : string
  ; reasons : WebpackReason.t list option
  ; request : string option
  }

let decode json =
  Json.Decode.
    { loc = json |> field "loc" string
    ; module_ = json |> field "module" string
    ; moduleIdentifier = json |> field "moduleIdentifier" string
    ; moduleName = json |> field "moduleName" string
    ; reasons = json |> optional (field "reasons" (list WebpackReason.decode))
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
      ; "reasons", r.reasons |> nullable (list WebpackReason.encode)
      ; "request", r.request |> nullable string
      ])
;;
