open State;

type action =
  | Next
  | Prev
  | Navigate(NavigationPath.Segment.t, int)
  | NavigateThroughBreadcrumbs(int)
  | UpdateComparisons(list(compare));

let updateNavigationPath = (path: list('a), segment, depth): list('a) => {
  let tail =
    if (List.length(path) < depth) {
      path;
    } else {
      Belt.List.take(path, depth) |> Utils.defaultTo([]);
    };

  [segment, ...tail |> List.rev] |> List.rev;
};

let reducer = (state, action) =>
  switch (action) {
  | Next => {
      index: (state.index + 1) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: [],
    }
  | Prev => {
      index:
        (state.index - 1 + List.length(state.comparisons))
        mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: [],
    }
  | Navigate(segment, depth) => {
      index: state.index,
      comparisons: state.comparisons,
      navigationPath:
        updateNavigationPath(state.navigationPath, segment, depth),
    }
  | NavigateThroughBreadcrumbs(index) => {
      index: state.index,
      comparisons: state.comparisons,
      navigationPath:
        Belt.List.take(state.navigationPath, index) |> Utils.defaultTo([]),
    }
  | UpdateComparisons(comparisons) => {
      index: 0,
      comparisons,
      navigationPath: [],
    }
  };

[@react.component]
let make = (~comparisons) => {
  let (state, dispatch) =
    React.useReducer(reducer, {index: 0, comparisons, navigationPath: []});

  if (List.length(state.comparisons) === 0) {
    <WelcomeScreen onStats={stats => dispatch(UpdateComparisons(stats))}>
      {loader =>
         <NavigationLayout
           side=React.null
           main=loader
           top={<Logo onClick={() => ()} />}
         />}
    </WelcomeScreen>;
  } else {
    let comp = List.nth(state.comparisons, state.index);
    let revPath = List.rev(state.navigationPath);
    let topContent =
      <>
        <Logo onClick={_ => dispatch(NavigateThroughBreadcrumbs(0))} />
        <Breadcrumbs
          items={state.navigationPath}
          onClick={index => dispatch(NavigateThroughBreadcrumbs(index))}
        />
        <ComparisonChooser
          comparisons={state.comparisons}
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

    <NavigationLayout side=sideContent main=mainContent top=topContent />;
  };
};