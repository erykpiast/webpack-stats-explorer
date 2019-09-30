let tap fn arg =
  let _ = fn arg in
  arg
;;

let defaultTo value option =
  match option with
  | Some s -> s
  | None -> value
;;

let identity (a : 'a) = a

module Function = struct
  let unary (fn : 'a) : 'a = [%raw "(a) => fn(a)"]
  let binary (fn : 'a) : 'a = [%raw "(a, b) => fn(a, b)"]
  let converge agg fns args = agg (List.map (fun fn -> fn args) fns)
  let all =  (List.fold_left (&&) true)
  let allPass (fns: (('a -> bool) list)) (args: 'a) = converge all fns args
  let curry fn arg1 = fn (arg1);;
  let uncurry fn (arg1) = fn arg1;;
  let curry2 fn arg1 arg2 = fn (arg1, arg2);;
  let uncurry2 fn (arg1, arg2) = fn arg1 arg2;;
end

module List = struct
  let rec isEqual a b ?eql:(eql=(=)) () =
    match a, b with
    | [], [] -> true
    | [ a ], [ b ] -> eql a b
    | aHead :: aTail, bHead :: bTail -> eql aHead bHead && isEqual aTail bTail ~eql ()
    | _, _ -> false
  ;;

  (* one of lists empty *)

  let diff isEqual a b =
    a |> List.filter (fun x -> b |> List.exists (fun y -> isEqual x y) |> not)
  ;;

  let uniq isEqual xs =
    List.fold_right
      (fun x acc -> if List.exists (fun y -> isEqual x y) acc then acc else x :: acc)
      xs
      []
  ;;

  let intersect isEqual a b =
    let longer, shorter = if List.length a > List.length b then a, b else b, a in
    longer
    |> List.filter (fun x -> shorter |> List.exists (fun y -> isEqual x y))
    |> uniq isEqual
  ;;

  let rec join separator list =
    match list with
    | [] -> []
    | [ head ] -> [ head ]
    | head :: tail -> head :: separator :: join separator tail
  ;;

  let nth index list = List.nth list index;;

  let findOpt isEqual list = Belt.List.getBy list isEqual;;

  let sumInt = List.fold_left (+) 0;;
end

module Array = struct
  let nth index array = Array.get array index;;

  let last array = nth (Array.length array - 1) array;;

  let trimLeft amount array = Js.Array.slice ~start:amount ~end_:(Js.Array.length array) array;;

  let filter = Js.Array.filter;;

  let join = Js.Array.joinWith;;
end

module String = struct
  let endsWith = Js.String.endsWith;;

  let split = Js.String.split;;
end

let pluralize singular plural n = (string_of_int n) ^ " " ^ (if n == 1 then singular else plural);;