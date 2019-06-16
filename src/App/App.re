open State;

type action =
  | Next
  | Prev
  | Navigate(NavigationPath.Segment.t, int)
  | NavigateThroughBreadcrumbs(int)
  | UpdateComparisons(list(Compare.t));

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
      let pathDepth = List.length(self.state.navigationPath);

      let sideContent =
        NavigationPath.Segment.(
          switch (revPath) {
          | [(Item.Module(_leaf), kind), (Item.Chunk(chunk), _kind), ..._] =>
            switch (chunk) {
            | Compare.Chunks.Summary(chunk) =>
              <ModulesList
                modules={chunk.modules}
                kind
                onModule={segment => self.send(Navigate(segment, 1))}
              />
            | Compare.Chunks.ModifiedSummary(chunk) =>
              <ModulesCompare
                modules={chunk.modules}
                onModule={segment => self.send(Navigate(segment, 1))}
              />
            }
          | [
              (Item.Module(_leaf), kind),
              (Item.Module(parent), _kind2),
              ..._,
            ] =>
            switch (parent) {
            | Compare.Modules.Summary(module_) =>
              <ModulesList
                modules={module_.modules}
                kind
                onModule={segment =>
                  self.send(Navigate(segment, pathDepth - 1))
                }
              />
            | Compare.Modules.ModifiedSummary(module_) =>
              switch (module_.modules) {
              | Some(modules) =>
                <ModulesCompare
                  modules
                  onModule={segment =>
                    self.send(Navigate(segment, pathDepth - 1))
                  }
                />
              | None => ReasonReact.null
              }
            }
          | _ =>
            <ChunksCompare
              chunks={comp.chunks}
              onChunk={chunk => self.send(Navigate(chunk, 0))}
            />
          }
        );
      let mainContent =
        switch (revPath) {
        | [] => <ChunksOverview size={comp.size} count={comp.count} />
        | segments =>
          segments
          |> List.hd
          |> (
            ((item, kind)) =>
              switch (item) {
              | Chunk(chunk) =>
                <ChunkSummary
                  data=chunk
                  kind
                  onModule={module_ => self.send(Navigate(module_, 1))}
                />
              | Module(module_) =>
                <ModuleSummary
                  data=module_
                  kind
                  onModule={module_ => self.send(Navigate(module_, 2))}
                />
              }
          )
        };
      let topContent =
        <>
          <Logo
            onClick={index => self.send(NavigateThroughBreadcrumbs(0))}
          />
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

      <NavigationLayout side=sideContent main=mainContent top=topContent />;
    },
};