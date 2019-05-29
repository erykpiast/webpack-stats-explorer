module ChunkSummary =
  GenericSummary.Make({
    open Compare.Chunks;

    type a = chunk;

    let componentName = "ChunkSummary";

    let getName = chunk =>
      switch (chunk) {
      | Summary(chunk) => chunk.name
      | ModifiedSummary(chunk) => chunk.name
      };

    let getSize = chunk =>
      switch (chunk) {
      | Summary(chunk) => chunk.size
      | ModifiedSummary(chunk) => fst(chunk.size)
      };

    let getModules = chunk =>
      (
        switch (chunk) {
        | Summary(chunk) => Compare.Modules.NotModifiedModules(chunk.modules)
        | ModifiedSummary(chunk) =>
          Compare.Modules.ModifiedModules(chunk.modules)
        }
      )
      |> (module_ => Some(module_));
    let getSource = _ => ReasonReact.null;
  });

let make = ChunkSummary.make;