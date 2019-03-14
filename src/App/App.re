type activeChunk =
  | Some(Compare.Chunks.chunk)
  | None;

type state = {
  index: int,
  comparisons: list(Compare.t),
  activeChunk: activeChunk
};

type action =
  | Next
  | Prev
  | ChooseChunk(Compare.Chunks.chunk)
  | UpdateComparisons(list(Compare.t));

let component = ReasonReact.reducerComponent("App");
let reducer = (action, state) =>
  switch (action) {
  | Next => ReasonReact.Update({
      index: (state.index + 1) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      activeChunk: None
    })
  | Prev => ReasonReact.Update({
      index: (state.index - 1 + List.length(state.comparisons)) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      activeChunk: None
    })
  | ChooseChunk(chunk) => ReasonReact.Update({
    index: state.index,
    comparisons: state.comparisons,
    activeChunk: Some(chunk)
  })
  | UpdateComparisons(comparisons) => ReasonReact.Update({
    index: 0,
    comparisons: comparisons,
    activeChunk: None
  })
};

module Styles = {
  open Css;

  let wrapper = style([
    display(`flex),
    width(`percent(100.0)),
  ]);

  let column = style([
    display(block),
    width(`percent(50.0)),
  ]);
};

let compareStats = (stats) => stats
  |> Array.to_list
  |> List.sort((a: Stats.t, b: Stats.t) => a.builtAt - b.builtAt)
  |> List.fold_left((acc: (option(Stats.t), list(Compare.t)), a) =>
    switch(acc) {
    | (None, []) => (Some(a), [])
    | (Some(b), acc) => (Some(b), [Compare.make(b, a), ...acc])
    | _ => acc
    }, (None, [])
  )
  |> snd
  |> List.rev;

let make = (~comparisons, _children) => {
  ...component,

  initialState: () => {
    index: 0,
    comparisons: comparisons,
    activeChunk: None
  },

  reducer,

  render: self => {
    let comp = List.nth(self.state.comparisons, self.state.index);

    <>
      <Dropzone onStats=(stats => self.send(UpdateComparisons(compareStats(stats)))) />
      <button onClick=(_ => self.send(Prev))>
        {ReasonReact.string("<<")}
      </button>
      {self.state.index + 1 |> string_of_int |> ReasonReact.string}
      {ReasonReact.string(" of ")}
      {self.state.comparisons |> List.length |> string_of_int |> ReasonReact.string}
      <button onClick=(_ => self.send(Next))>
        {ReasonReact.string(">>")}
      </button>
      <div className=Styles.wrapper>
        <div className=Styles.column>
          <ChunksCompare
            size=comp.size
            chunks=comp.chunks
            onChunk=((chunk) => self.send(ChooseChunk(chunk)))
          />
        </div>
        <div className=Styles.column>
          {switch self.state.activeChunk {
          | None => ReasonReact.null
          | Some(chunk) => Compare.Modules.(<ModulesCompare
            modules={switch chunk {
            | Summary(chunk) => NotModifiedModules(chunk.modules)
            | ModifiedSummary(chunk) => ModifiedModules(chunk.modules)
            }}
            onModule={(_) => ()}
            title={L10N.modules}
          />)}}
        </div>
      </div>
    </>
  }
};
