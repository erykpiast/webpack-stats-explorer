type 'a t = {
  added    : 'a list;
  modified : ('a * 'a) list;
  removed  : 'a list;
};;

let create isEqual xs ys =
  let diff = Utils.List.diff isEqual
  and intersect = Utils.List.intersect isEqual
  in {
    added = diff ys xs;
    modified = (intersect xs ys)
      |> List.map (fun z ->
        let findEqual = List.find (isEqual z)
        in (findEqual xs, findEqual ys)
      );
    removed = diff xs ys;
  };;

let encode encoder r = Json.Encode.(object_ [
  ("added",     r.added |> list encoder);
  ("modified",  r.modified |> list (tuple2 encoder encoder));
  ("removed",   r.removed |> list encoder);
])