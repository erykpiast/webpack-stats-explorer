open Json.Decode

type t = {
  loc               : string;
  module_           : string;
  moduleIdentifier  : string;
  moduleName        : string;
  reasons           : Reason.t array;
  request           : string;
};;

let decode json = {
  loc               = (json |> field "loc" string);
  module_           = (json |> field "module" string);
  moduleIdentifier  = (json |> field "moduleIdentifier" string);
  moduleName        = (json |> field "moduleName" string);
  reasons           = (json |> field "reasons" (array Reason.decode));
  request           = (json |> field "request" string);
};;
