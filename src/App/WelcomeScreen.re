let component = ReasonReact.statelessComponent("WelcomeScreen");

module Styles = {
  open Css;

  let dropzone = style([height(`percent(100.0))]);

  let wrapper =
    style([
      display(`flex),
      flexDirection(`column),
      height(`percent(100.0)),
      width(`percent(100.0)),
      justifyContent(`center),
      textAlign(`center),
    ]);

  let action =
    style([
      fontSize(em(1.5)),
      padding2(~v=Theme.Space.double, ~h=Theme.Space.quadruple),
    ]);
};

let logStats = (title, stats) => {
  Js.log(title);
  stats |> Stats.encode |> Js.log;
};

let logComp = (title, comp) => {
  Js.log(title);
  comp |> Compare.encode |> Js.log;
};

let loadExampleData = () => {
  [
    // logStats("a", Data.a);
    // logStats("b", Data.b);
    // logStats("c", Data.c);
    // logStats("d", Data.d);
    // logStats("e", Data.e);
    Compare.make(Data.a, Data.b),
    Compare.make(Data.b, Data.c),
    Compare.make(Data.c, Data.d),
    Compare.make(Data.d, Data.e),
  ];
};

let compareStats = stats =>
  stats
  |> Array.to_list
  |> List.sort((a: Stats.t, b: Stats.t) => a.builtAt - b.builtAt)
  |> List.fold_left(
       (acc: (option(Stats.t), list(Compare.t)), a) =>
         switch (acc) {
         | (None, []) => (Some(a), [])
         | (Some(b), acc) => (Some(a), [Compare.make(b, a), ...acc])
         | _ => acc
         },
       (None, []),
     )
  |> snd
  |> List.rev;

let make = (~onStats, children) => {
  ...component,
  render: _self => {
    <Dropzone
      className=Styles.dropzone
      onStats={stats => onStats(compareStats(stats))}>
      ...{onClick =>
        [|
          children(
            <div className=Styles.wrapper>
              <p> {L10N.drag |> ReasonReact.string} </p>
              <div>
                <Button onClick type_=Button.Primary className=Styles.action>
                  {L10N.upload |> ReasonReact.string}
                </Button>
              </div>
              <p> {L10N.or_ |> ReasonReact.string} </p>
              <div>
                <Button
                  onClick={_ => onStats(loadExampleData())}
                  className=Styles.action>
                  {L10N.loadExample |> ReasonReact.string}
                </Button>
              </div>
            </div>,
          ),
        |]
      }
    </Dropzone>;
  },
};