open Webapi.Url;;
open Webapi.Dom;;

type t =
  { urls: string list
  };;

let read () =
  let params = location |> Location.search |> URLSearchParams.make
  in let urls = params |> URLSearchParams.getAll("url") |> Array.to_list
  in { urls = urls };;

let write ({ urls }) =
  let search = Location.search location
  in let params = URLSearchParams.make search
  in let () = URLSearchParams.delete "url" params
  and updatedParams =
    List.fold_left (fun params url ->
      let () = URLSearchParams.append "url" url params
      in params
    ) params urls
  in let updatedSearch = URLSearchParams.toString updatedParams
  in
    if search != updatedSearch then
      let fakeHistoryState: History.state = [%raw "null"]
      in History.pushState fakeHistoryState "" ("?" ^ updatedSearch) history
;;
