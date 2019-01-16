type t = {
  loc               : string;
  module_           : string option;
  moduleId          : string option;
  moduleIdentifier  : string option;
  moduleName        : string option;
  type_             : string;
  userRequest       : string;
};;

let decode json = Json.Decode.({
  loc               = (json |> field "loc" string);
  module_           = (json |> field "module" (optional string));
  moduleId          = (json |> field "moduleId" (optional string));
  moduleIdentifier  = (json |> field "moduleIdentifier" (optional string));
  moduleName        = (json |> field "moduleName" (optional string));
  type_             = (json |> field "type" string);
  userRequest       = (json |> field "userRequest" string);
});;

let encode r = Json.Encode.(object_ [
  ("loc",               r.loc |> string);
  ("module",            r.module_ |> nullable string);
  ("moduleId",          r.moduleId |> nullable string);
  ("moduleIdentifier",  r.moduleIdentifier |> nullable string);
  ("moduleName",        r.moduleName |> nullable string);
  ("type",              r.type_ |> string);
  ("userRequest",       r.userRequest |> string);
]);;