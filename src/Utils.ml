let tap fn = (fun  arg -> let _ = (fn arg) in arg);;

let defaultTo value option = (match option with
| Some s -> s
| None -> value
);;

module List = struct
  let rec isEqual a b = match (a, b) with
    | ([], []) -> true
    | (a::[], b::[]) -> (a = b)
    | (aHead::aTail, bHead::bTail) -> (aHead = bHead && (isEqual aTail bTail))
    | (_, _) -> false (* one of lists empty *)
  ;;

  let diff isEqual a b = a |> List.filter (fun x -> (b |> (List.exists (fun y -> (isEqual x y))) |> not));;

  let uniq isEqual xs = List.fold_right (fun x acc ->
    if (List.exists (fun y -> isEqual x y) acc) then acc else x::acc
  ) xs [];;

  let intersect isEqual a b =
    let (longer, shorter) = if List.length(a) > List.length(b) then (a, b) else (b, a)
    in longer
      |> List.filter (fun x ->
        (shorter
          |> (List.exists (fun y -> (isEqual x y)))
        ))
      |> uniq isEqual;;

  let rec join separator list = match list with
    | [] -> []
    | head::[] -> [head]
    | head::tail -> head::separator::(join separator tail)
  ;;
end

module Function = struct
  let unary (fn: 'a) : 'a = [%raw "(a) => fn(a)" ];;
  let binary (fn: 'a) : 'a = [%raw "(a, b) => fn(a, b)" ];;
end
