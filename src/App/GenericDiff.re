module Styles = {
  open Css;

  let list =
    style([listStyleType(`none), padding(px(0)), margin(px(0))]);

  let item =
    style([
      display(`flex),
      justifyContent(`spaceBetween),
      marginBottom(Theme.Space.double),
      marginTop(Theme.Space.double),
    ]);

  let name =
    style([
      overflow(`hidden),
      flexShrink(1),
      marginRight(Theme.Space.default),
      textOverflow(`ellipsis),
      whiteSpace(`nowrap),
    ]);

  let size =
    style([
      marginLeft(`auto),
      marginRight(Theme.Space.default),
      color(Theme.Color.Text.secondary),
      flexShrink(0),
    ]);

  let diff = style([flexShrink(0)]);
};

let renderFilenames = filenames =>
  <>
    {ReasonReact.string(L10N.assets ++ ": ")}
    {switch (filenames) {
     | [a] => ReasonReact.string(a)
     | [_, b] => ReasonReact.string(b ++ {j|❗|j})
     | _ => ReasonReact.null
     }}
  </>;

module type Interface = {
  type a;
  let componentName: string;
};

module Make = (ToDiff: Interface) => {
  type props = {
    after: int,
    before: int,
    name: string,
    value: ToDiff.a,
    onChange: ToDiff.a => unit,
  };

  let component = ReasonReact.statelessComponent(ToDiff.componentName);

  let make = (~data, ~className="", _children) => {
    ...component,
    render: _self =>
      switch (data) {
      | [] => ReasonReact.null
      | _ =>
        <ul className={Cn.make([Styles.list, className])}>
          ...{
               data
               |> List.sort((a: props, b: props) => {
                    let aDiff = a.after - a.before;
                    let bDiff = b.after - b.before;
                    let diffOfDiffs = bDiff - aDiff;

                    if (diffOfDiffs === 0) {
                      0;
                    } else if (aDiff === 0) {
                      1;
                    } else if (bDiff === 0) {
                      (-1);
                    } else {
                      diffOfDiffs;
                    };
                  })
               |> List.map(({after, before, value, name, onChange}) =>
                    <li onClick={_ => onChange(value)} className=Styles.item>
                      <strong className=Styles.name title=name>
                        {ReasonReact.string(name)}
                      </strong>
                      {before !== 0 && after !== 0
                         ? <Size className=Styles.size value=after />
                         : ReasonReact.null}
                      <NumericDiff className=Styles.diff after before />
                    </li>
                  )
               |> Array.of_list
             }
        </ul>
      },
  };
};