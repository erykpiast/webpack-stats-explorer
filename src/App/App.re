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

let component = ReasonReact.reducerComponent("App");

let reducer = (action, state) =>
  switch (action) {
  | Next =>
    ReasonReact.Update({
      index: (state.index + 1) mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: [],
    })
  | Prev =>
    ReasonReact.Update({
      index:
        (state.index - 1 + List.length(state.comparisons))
        mod List.length(state.comparisons),
      comparisons: state.comparisons,
      navigationPath: [],
    })
  | Navigate(segment, depth) =>
    ReasonReact.Update({
      index: state.index,
      comparisons: state.comparisons,
      navigationPath:
        updateNavigationPath(state.navigationPath, segment, depth),
    })
  | NavigateThroughBreadcrumbs(index) =>
    ReasonReact.Update({
      index: state.index,
      comparisons: state.comparisons,
      navigationPath:
        Belt.List.take(state.navigationPath, index) |> Utils.defaultTo([]),
    })
  | UpdateComparisons(comparisons) =>
    ReasonReact.Update({index: 0, comparisons, navigationPath: []})
  };

let make = (~comparisons, _children) => {
  ...component,
  initialState: () => {index: 0, comparisons, navigationPath: []},
  reducer,
  render: self =>
    if (List.length(self.state.comparisons) === 0) {
      <WelcomeScreen onStats={stats => self.send(UpdateComparisons(stats))}>
        ...{loader =>
          <NavigationLayout side=ReasonReact.null main=loader top={<Logo />} />
        }
      </WelcomeScreen>;
    } else {
      let comp = List.nth(self.state.comparisons, self.state.index);
      let revPath = List.rev(self.state.navigationPath);
      let topContent =
        <>
          <Logo onClick={_ => self.send(NavigateThroughBreadcrumbs(0))} />
          <Breadcrumbs
            items={self.state.navigationPath}
            onClick={index => self.send(NavigateThroughBreadcrumbs(index))}
          />
          <ComparisonChooser
            comparisons={self.state.comparisons}
            currentIndex={self.state.index}
            onPrev={_ => self.send(Prev)}
            onNext={_ => self.send(Next)}
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
          navigationPath={self.state.navigationPath}
          onEntry={(level, entry) => self.send(Navigate(entry, level))}
        />;

      <NavigationLayout side=sideContent main=mainContent top=topContent />;
    },
};