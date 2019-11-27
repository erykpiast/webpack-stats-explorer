open State;

type action =
  | Next
  | Prev
  | Choose(int)
  | Navigate(NavigationPath.Segment.t, int)
  | NavigateThroughBreadcrumbs(int)
  | ToggleTimeline
  | UpdateStats(list(WebpackStats.t))
  | UpdateUrls(list(string));

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
      isTimelineVisible: state.isTimelineVisible,
      urls: state.urls,
    }
  | Prev => {
      index: (state.index - 1 + maxIndex) mod maxIndex,
      stats: state.stats,
      navigationPath: [],
      isTimelineVisible: state.isTimelineVisible,
      urls: state.urls,
    }
  | Choose(index) => {
      index,
      stats: state.stats,
      navigationPath: [],
      isTimelineVisible: state.isTimelineVisible,
      urls: state.urls,
    }
  | Navigate(segment, depth) => {
      index: state.index,
      stats: state.stats,
      navigationPath:
        updateNavigationPath(state.navigationPath, segment, depth),
      isTimelineVisible: state.isTimelineVisible,
      urls: state.urls,
    }
  | NavigateThroughBreadcrumbs(index) => {
      index: state.index,
      stats: state.stats,
      navigationPath:
        Belt.List.take(state.navigationPath, index) |> Utils.defaultTo([]),
      isTimelineVisible: state.isTimelineVisible,
      urls: state.urls,
    }
  | ToggleTimeline => {
      index: state.index,
      stats: state.stats,
      navigationPath: state.navigationPath,
      isTimelineVisible: !state.isTimelineVisible,
      urls: state.urls,
    }
  | UpdateStats(stats) => {
      index: 0,
      stats,
      navigationPath: [],
      isTimelineVisible: false,
      urls: state.urls,
    }
  | UpdateUrls(urls) => {
      index: state.index,
      stats: state.stats,
      navigationPath: state.navigationPath,
      isTimelineVisible: state.isTimelineVisible,
      urls,
    }
  };
};

[@react.component]
let make = (~stats) => {
  let (state, dispatch) =
    React.useReducer(
      reducer,
      {
        index: 0,
        stats,
        navigationPath: [],
        isTimelineVisible: false,
        urls: UrlState.read().urls,
      },
    );
  let comparisons = state.stats |> CompareStats.make;

  if (List.length(comparisons) === 0) {
    <WelcomeScreen
      onStats={stats => dispatch(UpdateStats(stats))}
      onUrls={urls => {
        Js.log(("oh my, URLS!", urls));
        dispatch(UpdateUrls(urls));
      }}
      urls={state.urls}>
      {loader =>
         <NavigationLayout
           side=React.null
           main=loader
           top={<Logo onClick={() => ()} />}
           aboveTop=React.null
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
        <ToggleTimeline
          isVisible={state.isTimelineVisible}
          onToggle={() => dispatch(ToggleTimeline)}
        />
      </>;

    let aboveTopContent =
      state.isTimelineVisible
        ? <Timeline
            stats={state.stats}
            selectedIndex={state.index}
            onChange={index => dispatch(Choose(index))}
          />
        : React.null;

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

    <NavigationLayout
      side=sideContent
      main=mainContent
      top=topContent
      aboveTop=aboveTopContent
    />;
  };
};