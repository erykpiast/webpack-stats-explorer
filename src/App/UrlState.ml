open Webapi.Url;;
open Webapi.Dom;;

type t =
  { urls: string list
  };;

let read () =
  let params = location |> Location.search |> URLSearchParams.make
  in let urls = params |> URLSearchParams.getAll("url") |> Array.to_list
  in { urls = urls };;
