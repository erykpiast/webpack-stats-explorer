open Rationale.Function.Infix;;
open Rationale.Option.Infix;;
open Webapi.Url;;
open Webapi.Dom;;

type t =
  { urls : string list
  ; navigationPath : string list
  ; index : int
  };;

let urlParameter = "u";;
let navigationPathParameters = "p";;
let indexParameter = "i";;
let navigationPathSeparator = ",";;

let extractNavigationPath params =
  params
  |> URLSearchParams.get navigationPathParameters
  <$> (Utils.String.split navigationPathSeparator ||> Array.to_list)
  |> Utils.defaultTo [];;

let extractIndex params =
  params
  |> URLSearchParams.get indexParameter
  >>= Belt.Int.fromString
  |> Utils.defaultTo 0;;

let read () =
  let params = location |> Location.search |> URLSearchParams.make
  in let urls = params |> URLSearchParams.getAll urlParameter |> Array.to_list
  and navigationPath = extractNavigationPath params
  and index = extractIndex params
  in
    { urls = urls
    ; navigationPath = navigationPath
    ; index = index
    };;

let write ({ urls; navigationPath; index }) =
  let search = Location.search location
  in let () = Js.log index
  in let params = URLSearchParams.make search
  in let _ = URLSearchParams.delete urlParameter params
    and _ = List.fold_left (fun params url ->
      let () = URLSearchParams.append urlParameter url params
      in params
    ) params urls
    and _ = URLSearchParams.delete navigationPathParameters params
    and _ = URLSearchParams.set
      navigationPathParameters
      (navigationPath |> Array.of_list |> Utils.Array.join navigationPathSeparator)
      params
    and _ = URLSearchParams.delete indexParameter params
    and _ = URLSearchParams.set
      indexParameter
      (index |> string_of_int)
      params
    and updatedSearch = URLSearchParams.toString params
  in
    if search != updatedSearch then
      let fakeHistoryState: History.state = [%raw "null"]
      in History.pushState fakeHistoryState "" ("?" ^ updatedSearch) history
;;
