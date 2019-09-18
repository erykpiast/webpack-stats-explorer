module ChunkSummary =
  GenericSummary.Make({
    open Compare.Chunks;

    type a = chunk;

    module Style = {
      open Css;

      let pointingContainer =
        style([
          height(`percent(100.0)),
          flexGrow(1.0),
          position(`relative),
        ]);

      let pointingArrow =
        style([position(`absolute), right(px(0)), top(px(0))]);
    };

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

    let getStatSize = getSize;
    let getOriginalSize = _ => None;
    let getParsedSize = _ => None;
    let getModules = chunk =>
      (
        switch (chunk) {
        | Summary(chunk) => Compare.Modules.NotModifiedModules(chunk.modules)
        | ModifiedSummary(chunk) =>
          Compare.Modules.ModifiedModules(chunk.modules)
        }
      )
      |> (module_ => Some(module_));
    let getSource = _ =>
      <div className=Style.pointingContainer>
        <PointingArrow
          direction=PointingArrow.ToRight className=Style.pointingArrow>
          {"Choose the" |> ReasonReact.string}
          <br />
          {"module here!" |> ReasonReact.string}
        </PointingArrow>
      </div>;
    let getOriginalSource = _ => None;
    let getParsedSource = _ => None;
  });

let make = ChunkSummary.make;