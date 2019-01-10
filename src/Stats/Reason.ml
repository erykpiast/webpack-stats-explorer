open Json.Decode

type t = {
  loc               : string;
  module_           : string option;
  moduleId          : string option;
  moduleIdentifier  : string option;
  moduleName        : string option;
  type_             : string;
  userRequest       : string;
};;

let decode json = {
  loc               = (json |> field "loc" string);
  module_           = (json |> field "module" (optional string));
  moduleId          = (json |> field "moduleId" (optional string));
  moduleIdentifier  = (json |> field "moduleIdentifier" (optional string));
  moduleName        = (json |> field "moduleName" (optional string));
  type_             = (json |> field "type" string);
  userRequest       = (json |> field "userRequest" string);
};;
