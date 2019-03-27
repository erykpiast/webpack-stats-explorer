open State;

type action =
  | Next
  | Prev
  | Navigate(NavigationPath.Segment.t)
  | UpdateComparisons(list(Compare.t));

let component = ReasonReact.reducerComponent("App");

let reducer = (action, state) => switch (action) {
  | Next => ReasonReact.Update({
      index: (state.index + 1) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: []
    })
  | Prev => ReasonReact.Update({
      index: (state.index - 1 + List.length(state.comparisons)) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: []
    })
  | Navigate(segment) => ReasonReact.Update({
    index: state.index,
    comparisons: state.comparisons,
    navigationPath: [segment]
  })
  | UpdateComparisons(comparisons) => ReasonReact.Update({
    index: 0,
    comparisons: comparisons,
    navigationPath: []
  })
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

let renderMainContent = (navigationPath) => switch (navigationPath) {
  | [] => ReasonReact.null
  | [(item, kind), ..._] => NavigationPath.Segment.Item.(switch (item) {
    | Module(_) => ReasonReact.null
    | Chunk(chunk) => <ChunkSummary chunk=chunk kind=kind />
    })
};

let make = (~comparisons, _children) => {
  ...component,

  initialState: () => {
    index: 0,
    comparisons: comparisons,
    navigationPath: [],
  },

  reducer,

  render: self => {
    let comp = List.nth(self.state.comparisons, self.state.index);

    let sideContent = <ChunksCompare
      size=comp.size
      chunks=comp.chunks
      onChunk=((chunk) => self.send(Navigate(chunk)))
    />;
    let mainContent = renderMainContent(self.state.navigationPath);

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
      <Breadcrumbs items=self.state.navigationPath />
      <NavigationLayout side=sideContent main=mainContent />
    </>
  }
};
