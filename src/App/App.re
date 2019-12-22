type action =
  | Next
  | Prev
  | Choose(int)
  | Navigate(State.NavigationPath.Segment.t, int)
  | NavigateThroughBreadcrumbs(int)
  | ToggleTimeline
  | UpdateStats(list(WebpackStats.t))
  | UpdateUrls(list(string))
  | SelectTab(int);

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
  State.(
    {
      let maxIndex = List.length(state.stats) - 1;

      switch (action) {
      | Next => {
          tab: state.tab,
          index: (state.index + 1) mod maxIndex,
          stats: state.stats,
          navigationPath: [],
          isTimelineVisible: state.isTimelineVisible,
          urls: state.urls,
        }
      | Prev => {
          tab: state.tab,
          index: (state.index - 1 + maxIndex) mod maxIndex,
          stats: state.stats,
          navigationPath: [],
          isTimelineVisible: state.isTimelineVisible,
          urls: state.urls,
        }
      | Choose(index) => {
          tab: state.tab,
          index,
          stats: state.stats,
          navigationPath: [],
          isTimelineVisible: state.isTimelineVisible,
          urls: state.urls,
        }
      | Navigate(segment, depth) => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath:
            updateNavigationPath(state.navigationPath, segment, depth),
          isTimelineVisible: state.isTimelineVisible,
          urls: state.urls,
        }
      | NavigateThroughBreadcrumbs(index) => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath:
            Belt.List.take(state.navigationPath, index)
            |> Utils.defaultTo([]),
          isTimelineVisible: state.isTimelineVisible,
          urls: state.urls,
        }
      | ToggleTimeline => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: !state.isTimelineVisible,
          urls: state.urls,
        }
      | UpdateStats(stats) => {
          tab: state.tab,
          index: Js.Math.min_int(state.index, List.length(stats)),
          stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: false,
          urls: state.urls,
        }
      | UpdateUrls(urls) => {
          tab: 1,
          index: 0,
          stats: [],
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          urls,
        }
      | SelectTab(tab) => {
          tab,
          index: state.index,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          urls: state.urls,
        }
      };
    }
  );

[@react.component]
let make = (~stats) => {
  let urlState = UrlState.read();
  let (state, dispatch) =
    React.useReducer(
      reducer,
      {
        tab: urlState.tab,
        index: urlState.index,
        stats,
        navigationPath:
          urlState.navigationPath
          |> List.map(State.NavigationPath.Segment.fromString)
          |> List.filter((!=)(None))
          |> List.map(Belt.Option.getExn),
        isTimelineVisible: false,
        urls: urlState.urls,
      },
    );
  React.useEffect4(
    () => {
      UrlState.{
        urls: state.urls,
        navigationPath:
          state.navigationPath
          |> List.map(State.NavigationPath.Segment.toString),
        index: state.index,
        tab: state.tab,
      }
      |> UrlState.write;
      None;
    },
    (state.urls, state.navigationPath, state.index, state.tab),
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
    let navigationPath =
      state.navigationPath
      |> NavigationPath.fromState(CompareEntry.ModifiedChildren(comp));
    let revPath = navigationPath |> List.rev;
    let topContent =
      <>
        <Logo onClick={_ => dispatch(NavigateThroughBreadcrumbs(0))} />
        <Breadcrumbs
          items=navigationPath
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
      | [(entry, kind), ..._] =>
        <EntrySummary
          tab={state.tab}
          onTab={tab => dispatch(SelectTab(tab))}
          entry
          kind
        />
      };

    let sideContent =
      <EntryTree
        comp
        navigationPath
        onEntry={(level, segment) =>
          Navigate(NavigationPath.Segment.toState(segment), level)
          |> dispatch
        }
      />;

    <NavigationLayout
      side=sideContent
      main=mainContent
      top=topContent
      aboveTop=aboveTopContent
    />;
  };
};