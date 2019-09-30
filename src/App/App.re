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
      <WelcomeScreen
        onStats={stats =>
          self.send(
            UpdateComparisons(stats |> List.map(stat => Entry(stat))),
          )
        }>
        ...{loader =>
          <NavigationLayout side=ReasonReact.null main=loader top={<Logo />} />
        }
      </WelcomeScreen>;
    } else {
      let comp = List.nth(self.state.comparisons, self.state.index);
      let revPath = List.rev(self.state.navigationPath);
      let pathDepth = List.length(self.state.navigationPath);
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

      switch (comp) {
      | Legacy(comp) =>
        let sideContent =
          NavigationPath.Segment.(
            switch (revPath) {
            | [
                (Item.Module(leaf), kind),
                (Item.Chunk(chunk), _kind),
                ..._,
              ] =>
              let leafName =
                switch (leaf) {
                | Summary(module_) => module_.name
                | ModifiedSummary(module_) => module_.name
                };
              switch (chunk) {
              | Compare.Chunks.Summary(chunk) =>
                <ModulesList
                  modules={chunk.modules}
                  kind
                  onModule={segment => self.send(Navigate(segment, 1))}
                  selected={Some(leafName)}
                />
              | Compare.Chunks.ModifiedSummary(chunk) =>
                <ModulesCompare
                  modules={chunk.modules}
                  onModule={segment => self.send(Navigate(segment, 1))}
                  selected={Some(leafName)}
                />
              };
            | [
                (Item.Module(leaf), kind),
                (Item.Module(parent), _kind2),
                ..._,
              ] =>
              let leafName =
                switch (leaf) {
                | Summary(module_) => module_.name
                | ModifiedSummary(module_) => module_.name
                };

              switch (parent) {
              | Compare.Modules.Summary(module_) =>
                <ModulesList
                  modules={module_.modules}
                  kind
                  onModule={segment =>
                    self.send(Navigate(segment, pathDepth - 1))
                  }
                  selected={Some(leafName)}
                />
              | Compare.Modules.ModifiedSummary(module_) =>
                switch (module_.modules) {
                | Some(modules) =>
                  <ModulesCompare
                    modules
                    onModule={segment =>
                      self.send(Navigate(segment, pathDepth - 1))
                    }
                    selected={Some(leafName)}
                  />
                | None => ReasonReact.null
                }
              };
            | [(Item.Chunk(leaf), _kind)] =>
              let leafName =
                switch (leaf) {
                | Summary(chunk) => chunk.name
                | ModifiedSummary(chunk) => chunk.name
                };
              <ChunksCompare
                chunks={comp.chunks}
                onChunk={chunk => self.send(Navigate(chunk, 0))}
                selected={Some(leafName)}
              />;
            | _ =>
              <ChunksCompare
                chunks={comp.chunks}
                onChunk={chunk => self.send(Navigate(chunk, 0))}
                selected=None
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
                    selected={Some(chunk)}
                  />
                | Module(module_) =>
                  <ModuleSummary
                    data=module_
                    kind
                    onModule={module_ => self.send(Navigate(module_, 2))}
                    selected={Some(module_)}
                  />
                | Entry(entry) =>
                  <EntrySummary
                    data=entry
                    kind
                    onEntry={entry => self.send(Navigate(entry, 2))}
                    selected={Some(entry)}
                  />
                }
            )
          };

        <NavigationLayout side=sideContent main=mainContent top=topContent />;
      | Entry(comp) =>
        open NavigationPath.Segment;

        let sideContent =
          switch (revPath) {
          | [(Item.Entry(leaf), _kind)] =>
            let leafName =
              switch (leaf) {
              | Entry({id}) => id
              | ModifiedEntry({id}) => id
              };
            <EntryCompare
              entries=comp
              onEntry={entry => self.send(Navigate(entry, 0))}
              selected={Some(leafName)}
            />;
          | [(Item.Entry(leaf), kind), (Item.Entry(parent), _kind), ..._] =>
            let leafId =
              switch (leaf) {
              | Entry({id}) => id
              | ModifiedEntry({id}) => id
              };
            switch (parent) {
            | ModifiedEntry(entry) =>
              <EntryCompare
                entries={entry.children}
                onEntry={entry => self.send(Navigate(entry, pathDepth - 1))}
                selected={Some(leafId)}
              />
            | Entry(entry) =>
              <EntryList
                entries={entry.children}
                kind
                onEntry={entry => self.send(Navigate(entry, pathDepth - 1))}
                selected={Some(leafId)}
              />
            };
          | [] =>
            <EntryCompare
              entries=comp
              onEntry={entry => self.send(Navigate(entry, pathDepth - 1))}
              selected=None
            />
          | _ => ReasonReact.null
          };
        let mainContent =
          switch (revPath) {
          | [] =>
            <EntryOverview
              size={comp |> CompareEntry.size}
              count={comp |> CompareEntry.count |> snd}
            />
          | segments =>
            segments
            |> List.hd
            |> (
              ((item, kind)) =>
                switch (item) {
                | Chunk(_) => ReasonReact.null
                | Module(_) => ReasonReact.null
                | Entry(entry) =>
                  <EntrySummary
                    data=entry
                    kind
                    onEntry={entry => self.send(Navigate(entry, 2))}
                    selected={Some(entry)}
                  />
                }
            )
          };

        <NavigationLayout side=sideContent main=mainContent top=topContent />;
      };
    },
};