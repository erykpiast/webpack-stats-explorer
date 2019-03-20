open State;

type action =
  | Next
  | Prev
  | Navigate(NavigationPath.segment)
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

let getModules = (item) => switch (item) {
  | Chunk(chunk) => switch (chunk) {
    | Summary(chunk) => Compare.Modules.NotModifiedModules(chunk.modules)
    | ModifiedSummary(chunk) => Compare.Modules.ModifiedModules(chunk.modules)
  }
  | Module(module_) => switch (module_) {
    | Summary(module_) => Compare.Modules.NotModifiedModules(module_.modules)
    | ModifiedSummary(module_) => switch (module_.modules) {
      | Some(modules) => Compare.Modules.ModifiedModules(modules)
      | None => Compare.Modules.NotModifiedModules([])
    }
  }
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
      <div className=Styles.wrapper>
        <div className=Styles.column>
          <ChunksCompare
            size=comp.size
            chunks=comp.chunks
            onChunk=((chunk) => self.send(Navigate(chunk)))
          />
        </div>
        <div className=Styles.column>
          {switch self.state.navigationPath {
          | [] => ReasonReact.null
          | [chunk] => <ModulesCompare
            modules={switch (chunk) {
            | NavigationPath.Added(item) => getModules(item)
            | NavigationPath.Removed(item) => getModules(item)
            | NavigationPath.Modified(item) => getModules(item)
            | NavigationPath.Intact(item) => getModules(item)
            }}
            onModule={(_) => ()}
            title={L10N.modules}
          />}}
        </div>
      </div>
    </>
  }
};
