type state = {
  index: int,
  comparisons: list(Compare.t),
};

type action =
  | Next
  | Prev;

let component = ReasonReact.reducerComponent("App");
let reducer = (action, state) =>
  switch (action) {
  | Next => ReasonReact.Update({
      index: (state.index + 1) mod List.length(state.comparisons),
      comparisons: state.comparisons
    })
  | Prev => ReasonReact.Update({
      index: (state.index - 1 + List.length(state.comparisons)) mod List.length(state.comparisons),
      comparisons: state.comparisons
    })
};

/* greeting and children are props. `children` isn't used, therefore ignored.
    We ignore it by prepending it with an underscore */
let make = (~comparisons, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => {
    index: 0,
    comparisons: comparisons
  },

  /* State transitions */
  reducer,

  render: self => {
    let comp = List.nth(self.state.comparisons, self.state.index);

    <>
      <button onClick=(_ => self.send(Prev))>
        {ReasonReact.string("<<")}
      </button>
      {self.state.index + 1 |> string_of_int |> ReasonReact.string}
      {ReasonReact.string(" of ")}
      {self.state.comparisons |> List.length |> string_of_int |> ReasonReact.string}
      <button onClick=(_ => self.send(Next))>
        {ReasonReact.string(">>")}
      </button>
      <VisCompare
        size=comp.size
        chunks=comp.chunks
      />
    </>
  }
};
