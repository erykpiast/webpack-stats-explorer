open State;

type action =
  | Next
  | Prev
  | Navigate(NavigationPath.Segment.t, int)
  | NavigateThroughBreadcrumbs(int)
  | UpdateStats(list(WebpackStats.t));

let updateNavigationPath = (path: list('a), segment, depth): list('a) => {
  let tail =
    if (List.length(path) < depth) {
      path;
    } else {
      Belt.List.take(path, depth) |> Utils.defaultTo([]);
    };

  [segment, ...tail |> List.rev] |> List.rev;
};

let reducer = (state, action) => {
  let maxIndex = List.length(state.stats) - 1;

  switch (action) {
  | Next => {
      index: (state.index + 1) mod maxIndex,
      stats: state.stats,
      navigationPath: [],
    }
  | Prev => {
      index: (state.index - 1 + maxIndex) mod maxIndex,
      stats: state.stats,
      navigationPath: [],
    }
  | Navigate(segment, depth) => {
      index: state.index,
      stats: state.stats,
      navigationPath:
        updateNavigationPath(state.navigationPath, segment, depth),
    }
  | NavigateThroughBreadcrumbs(index) => {
      index: state.index,
      stats: state.stats,
      navigationPath:
        Belt.List.take(state.navigationPath, index) |> Utils.defaultTo([]),
    }
  | UpdateStats(stats) => {index: 0, stats, navigationPath: []}
  };
};

[@react.component]
let make = (~stats) => {
  let (state, dispatch) =
    React.useReducer(reducer, {index: 0, stats, navigationPath: []});
  let comparisons = state.stats |> CompareStats.make;

  if (List.length(comparisons) === 0) {
    <WelcomeScreen onStats={stats => dispatch(UpdateStats(stats))}>
      {loader =>
         <NavigationLayout
           side=React.null
           main=loader
           top={<Logo onClick={() => ()} />}
         />}
    </WelcomeScreen>;
  } else {
    let comp = List.nth(comparisons, state.index);
    let revPath = List.rev(state.navigationPath);
    let topContent =
      <>
        <Logo onClick={_ => dispatch(NavigateThroughBreadcrumbs(0))} />
        <Breadcrumbs
          items={state.navigationPath}
          onClick={index => dispatch(NavigateThroughBreadcrumbs(index))}
        />
        <ComparisonChooser
          comparisons
          currentIndex={state.index}
          onPrev={_ => dispatch(Prev)}
          onNext={_ => dispatch(Next)}
        />
      </>;

    let mainContent =
      switch (revPath) {
      | [] =>
        <EntryOverview
          size={comp |> CompareEntry.size}
          count={comp |> CompareEntry.count |> snd}
        />
      | [(entry, kind), ..._] => <EntrySummary entry kind />
      };

    let sideContent =
      <EntryTree
        comp
        navigationPath={state.navigationPath}
        onEntry={(level, entry) => dispatch(Navigate(entry, level))}
      />;

    <>
      <Timeline stats={state.stats} selectedIndex={state.index} />
      <NavigationLayout side=sideContent main=mainContent top=topContent />
    </>;
  };
};