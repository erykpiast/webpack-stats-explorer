type action =
  | Next
  | Prev
  | Choose(int)
  | Navigate(State.NavigationPath.Segment.t, int)
  | NavigateThroughBreadcrumbs(int)
  | NavigateAbsolutely(list(State.NavigationPath.Segment.t))
  | ToggleTimeline
  | ToggleSidebar
  | AddStats(list(WebpackStats.t))
  | UpdateUrls(list(string))
  | SelectTab(int)
  | SelectDiffMode(CodeDiff.mode)
  | SwitchSourceTree
  | SetUrlState(State.t)
  | StartOver;

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
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | Prev => {
          tab: state.tab,
          index: (state.index - 1 + maxIndex) mod maxIndex,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | Choose(index) => {
          tab: state.tab,
          index,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | Navigate(segment, depth) => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath:
            updateNavigationPath(state.navigationPath, segment, depth),
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | NavigateThroughBreadcrumbs(index) => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath:
            Belt.List.take(state.navigationPath, index)
            |> Utils.defaultTo([]),
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | NavigateAbsolutely(navigationPath) => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | ToggleTimeline => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: !state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | ToggleSidebar => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: !state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | AddStats(stats) => {
          tab: state.tab,
          index: state.index,
          stats: List.concat([state.stats, stats]),
          navigationPath: state.navigationPath,
          isSidebarCollapsed: state.isSidebarCollapsed,
          isTimelineVisible: false,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | UpdateUrls(urls) => {
          tab: 1,
          index: 0,
          stats: [],
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls,
          sourceTree: state.sourceTree,
        }
      | SelectTab(tab) => {
          tab,
          index: state.index,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | SwitchSourceTree => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath:
            state.sourceTree
              ? State.NavigationPath.convertFromSourceTree(
                  state.navigationPath,
                )
              : State.NavigationPath.convertToSourceTree(state.navigationPath),
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: state.urls,
          sourceTree: !state.sourceTree,
        }
      | SelectDiffMode(diffMode) => {
          tab: state.tab,
          index: state.index,
          stats: state.stats,
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed:
            CodeDiff.(
              switch (diffMode) {
              | Unified => false
              | Split => true
              }
            ),
          diffMode,
          urls: state.urls,
          sourceTree: state.sourceTree,
        }
      | StartOver => {
          tab: state.tab,
          index: state.index,
          stats: [],
          navigationPath: state.navigationPath,
          isTimelineVisible: state.isTimelineVisible,
          isSidebarCollapsed: state.isSidebarCollapsed,
          diffMode: state.diffMode,
          urls: [],
          sourceTree: state.sourceTree,
        }
      | SetUrlState(newState) =>
        if (newState != state) {
          newState;
        } else {
          state;
        }
      };
    }
  );

let getStateFromUrl = (state, urlState: UrlState.t) => {
  let currentState =
    switch (state) {
    | Some(existingState) => existingState
    | None =>
      State.{
        tab: 0,
        index: 0,
        stats: [],
        navigationPath: [],
        isTimelineVisible: false,
        isSidebarCollapsed: false,
        diffMode: CodeDiff.Unified,
        urls: [],
        sourceTree: false,
      }
    };

  State.{
    tab: urlState.tab,
    index: urlState.index,
    stats: currentState.stats,
    navigationPath:
      urlState.navigationPath
      |> List.map(State.NavigationPath.Segment.fromString),
    isTimelineVisible: urlState.timeline,
    isSidebarCollapsed: currentState.isSidebarCollapsed,
    diffMode: urlState.splitView ? CodeDiff.Split : CodeDiff.Unified,
    urls: urlState.urls,
    sourceTree: urlState.sourceTree,
  };
};

[@react.component]
let make = () => {
  let urlState = UrlState.read();
  let (state, dispatch) =
    React.useReducer(reducer, getStateFromUrl(None, urlState));
  React.useEffect5(
    () => {
      UrlState.{
        urls: state.urls,
        navigationPath:
          state.navigationPath
          |> List.map(State.NavigationPath.Segment.toString),
        index: state.index,
        tab: state.tab,
        sourceTree: state.sourceTree,
        splitView: state.diffMode === CodeDiff.Split,
        timeline: state.isTimelineVisible,
      }
      |> UrlState.write;
      None;
    },
    (
      state.urls,
      state.navigationPath,
      state.index,
      state.tab,
      state.sourceTree,
    ),
  );

  React.useEffect(
    Webapi.Dom.(
      () => {
        let windowTarget = Window.asEventTarget(window);

        let popstateHandler = _ => {
          dispatch(
            SetUrlState(getStateFromUrl(Some(state), UrlState.read())),
          );
        };

        EventTarget.addEventListener(
          "popstate",
          popstateHandler,
          windowTarget,
        );

        Some(
          () => {
            EventTarget.removeEventListener(
              "popstate",
              popstateHandler,
              windowTarget,
            )
          },
        );
      }
    ),
  );

  let comparisons =
    (
      switch (state.stats) {
      | [singleStat] => [singleStat, singleStat]
      | multipleStats => multipleStats
      }
    )
    |> CompareStats.make(state.sourceTree);

  if (List.length(comparisons) === 0) {
    <WelcomeScreen
      onStats={stats => dispatch(AddStats(stats))}
      onUrls={urls => dispatch(UpdateUrls(urls))}
      urls={state.urls}>
      {loader =>
         <NavigationLayout
           side=React.null
           main=loader
           top={<Logo onClick={() => ()} />}
           aboveTop=React.null
           isSidebarCollapsed={state.isSidebarCollapsed}
           onSidebarToggle={() => dispatch(ToggleSidebar)}
         />}
    </WelcomeScreen>;
  } else {
    <AddStats onStats={stats => dispatch(AddStats(stats))}>
      {(triggerUpload, _) => {
         let comp = List.nth(comparisons, state.index);
         let navigationPath =
           state.navigationPath
           |> NavigationPath.fromState(CompareEntry.ModifiedChildren(comp));
         let revPath = navigationPath |> List.rev;
         let topContent =
           <>
             <Logo
               onClick={_ =>
                 if (List.length(navigationPath) === 0) {
                   dispatch(StartOver);
                 } else {
                   dispatch(NavigateThroughBreadcrumbs(0));
                 }
               }
             />
             <Breadcrumbs
               items={state.navigationPath}
               onClick={index => dispatch(NavigateThroughBreadcrumbs(index))}
             />
             <AddStatsButton onClick=triggerUpload />
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
               level=`top
             />
           | [entry] =>
             let (size, count, name) =
               CompareEntry.(
                 switch (entry) {
                 | Entry(entry) =>
                   let kind =
                     CompareEntry.kind(comp, CompareEntry.Entry(entry), []);
                   let size =
                     switch (kind) {
                     | Added => (0, entry.size)
                     | Removed => (entry.size, 0)
                     | Intact => (entry.size, entry.size)
                     | _ => (0, 0)
                     };

                   (size, List.length(entry.children), entry.id);
                 | ModifiedEntry(entry) => (
                     entry.size,
                     entry.children |> CompareEntry.count |> snd,
                     entry.id,
                   )
                 }
               );

             <EntryOverview size count name level=`chunk />;
           | [entry, ...rest] =>
             let kind = CompareEntry.kind(comp, entry, rest);

             <EntrySummary
               entry
               kind
               tab={state.tab}
               diffMode={state.diffMode}
               onTab={tab => dispatch(SelectTab(tab))}
               onDiffMode={diffMode => dispatch(SelectDiffMode(diffMode))}
             />;
           };

         let treeSwitcher =
           <SourceTreeSwitcher
             selected={state.sourceTree}
             onSwitch={() => dispatch(SwitchSourceTree)}
           />;
         let entryTree =
           <EntryTree
             comp
             navigationPath
             onEntry={(level, segment) =>
               Navigate(NavigationPath.Segment.toState(segment), level)
               |> dispatch
             }
             onPath={path =>
               NavigateAbsolutely(
                 path |> List.map(NavigationPath.Segment.toState),
               )
               |> dispatch
             }
           />;

         let sideContent = <Sidebar scrollable=entryTree fixed=treeSwitcher />;

         <NavigationLayout
           side=sideContent
           main=mainContent
           top=topContent
           aboveTop=aboveTopContent
           isSidebarCollapsed={state.isSidebarCollapsed}
           onSidebarToggle={() => dispatch(ToggleSidebar)}
         />;
       }}
    </AddStats>;
  };
};
