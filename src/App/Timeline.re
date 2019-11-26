open Rationale.Function;
open Rationale.Option;

module Styles = {
  open Css;

  let root = style([]);

  let clickableArea = style([cursor(`pointer)]);
};

type name = string;
type timestamp = int;

type datum = {
  name,
  timestamp,
  size: float,
};

[@bs.deriving {abstract: light}]
type payload = {
  name: string,
  color: string,
  value: float,
};

[@bs.deriving {abstract: light}]
type contentProps = {payload: array(payload)};

[@bs.deriving {abstract: light}]
type onClickProps = {index: int};

module TimestampNameMap =
  Map.Make({
    type t = (timestamp, name);
    let compare = ((tA, nA), (tB, nB)) =>
      switch (Pervasives.compare(tA, tB)) {
      | 0 => Pervasives.compare(nA, nB)
      | c => c
      };
  });

module NameSet =
  Set.Make({
    type t = name;
    let compare = Pervasives.compare;
  });

let toJs = Array.map(d => {"timestamp": d.timestamp, "size": d.size});

let formatDate =
  float_of_int
  ||> Js.Date.fromFloat
  ||> ReasonDateFns.DateFns.lightFormat("yyyy-MM-dd hh:mm");

let getChunkColor = colors =>
  flip((mod), List.length(colors))
  ||> (colors |> List.map(Css.Types.Color.toString) |> List.nth);

let getStrokeColor =
  Theme.Color.Chart.Stroke.[
    Green.light,
    Green.normal,
    Green.dark,
    Yellow.light,
    Yellow.normal,
    Yellow.dark,
    Red.light,
    Red.normal,
    Red.dark,
    Blue.light,
    Blue.normal,
    Blue.dark,
  ]
  |> getChunkColor;

let getFillColor =
  Theme.Color.Chart.Fill.[
    Green.light,
    Green.normal,
    Green.dark,
    Yellow.light,
    Yellow.normal,
    Yellow.dark,
    Red.light,
    Red.normal,
    Red.dark,
    Blue.light,
    Blue.normal,
    Blue.dark,
  ]
  |> getChunkColor;

[@react.component]
let make = (~className="", ~stats=[], ~onChange, ~selectedIndex) => {
  let (rootWidth, setRootWidth) = React.useState(() => 0);
  let (rootElement, setRootElement) = React.useState(() => Js.Nullable.null);
  let getRootWidth =
    Js.Nullable.toOption
    ||> fmap(
          (
            (element, _) =>
              Webapi.Dom.(
                Element.getBoundingClientRect(element)
                |> DomRect.width
                |> int_of_float
              )
          )
          ||> setRootWidth,
        );
  let resizeHandler = _ => getRootWidth(rootElement) |> ignore;
  Webapi.Dom.(
    React.useEffect(() => {
      Window.addEventListener("resize", resizeHandler, window);

      Some(
        () => Window.removeEventListener("resize", resizeHandler, window),
      );
    })
  );

  let (names, timestamps, datumMap) =
    stats
    |> List.fold_left(
         (
           (names, timestamps, datumMap): (
             NameSet.t,
             list(timestamp),
             TimestampNameMap.t(datum),
           ),
           stat: WebpackStats.t,
         ) => {
           let entryFromChunk = Entry.FromChunk.make(stat.assets);

           stat.chunks
           |> List.fold_left(
                ((set, list, map), chunk) => {
                  let entry = entryFromChunk(chunk);
                  let datum = {
                    name: entry.id,
                    size: entry.size |> float_of_int,
                    timestamp: stat.builtAt,
                  };
                  (
                    NameSet.add(datum.name, set),
                    list,
                    TimestampNameMap.add(
                      (stat.builtAt, datum.name),
                      datum,
                      map,
                    ),
                  );
                },
                (names, List.append(timestamps, [stat.builtAt]), datumMap),
              );
         },
         (NameSet.empty, [], TimestampNameMap.empty),
       );

  let uniqNames = NameSet.elements(names);

  let maxSize =
    datumMap
    |> TimestampNameMap.bindings
    |> List.map(((_key, {size})) => size)
    |> Array.of_list
    |> Js.Math.maxMany_float;
  let sizeUnit = maxSize |> int_of_float |> Size.guessUnit;
  let sizeDivider =
    (
      switch (sizeUnit) {
      | Size.B => 1
      | Size.KB => 1024
      | Size.MB => 1024 * 1024
      }
    )
    |> float_of_int;

  let data =
    timestamps
    |> List.map(timestamp =>
         uniqNames
         |> List.fold_left(
              (acc, name) => {
                let mapKey = (timestamp, name);
                if (TimestampNameMap.mem(mapKey, datumMap)) {
                  let {size} = TimestampNameMap.find(mapKey, datumMap);

                  [(name, size /. sizeDivider), ...acc];
                } else {
                  [(name, 0.0), ...acc];
                };
              },
              [("timestamp", timestamp |> float_of_int)],
            )
         |> Js.Dict.fromList
       )
    |> Array.of_list;

  BsRecharts.(
    <div
      className={Cn.make([className, Styles.root])}
      ref={ReactDOMRe.Ref.callbackDomRef(element => {
        setRootElement(_ => element);
        getRootWidth(element) |> ignore;
      })}>
      <AreaChart data width=rootWidth height=300>
        {uniqNames
         |> List.mapi((index, name) =>
              <Area
                dataKey=name
                stroke={getStrokeColor(index)}
                fill={getFillColor(index)}
                key=name
                stackId="1"
              />
            )
         |> Array.of_list
         |> React.array}
        {stats
         |> List.mapi((index, {builtAt}: WebpackStats.t) => {
              let x1 = builtAt |> string_of_int;
              let x2 =
                if (List.length(stats) > index + 1) {
                  List.nth(stats, index + 1).builtAt |> string_of_int;
                } else {
                  x1;
                };

              let (stroke, fill) =
                if (index === selectedIndex) {
                  (
                    Theme.Color.Border.default |> Css.Types.Color.toString,
                    "transparent",
                  );
                } else {
                  ("transparent", "#fff");
                };

              <ReferenceArea
                className=Styles.clickableArea
                x1
                x2
                fill
                stroke
                onClick={(_, _) => onChange(index)}
              />;
            })
         |> Array.of_list
         |> React.array}
        <XAxis dataKey="timestamp" tickFormatter=formatDate />
        <YAxis
          allowDecimals=false
          tickFormatter={tick => tick == 0 ? "" : string_of_int(tick)}
          mirror=true
          unit={sizeUnit |> Size.displayUnit}
        />
        <Tooltip
          formatter={value =>
            switch (value) {
            | 0.0 => Js.Nullable.null
            | value =>
              Js.Float.toFixedWithPrecision(~digits=2, value)
              ++ " "
              ++ Size.displayUnit(sizeUnit)
              |> Js.Nullable.return
            }
          }
          labelFormatter=formatDate
          content={(props: contentProps) =>
            <TimelineTooltip
              sizeUnit
              payload={
                props->payload
                |> Array.map(payload =>
                     TimelineTooltip.{
                       name: payload->name,
                       color: payload->color,
                       value: payload->value *. sizeDivider,
                     }
                   )
              }
            />
          }
        />
      </AreaChart>
    </div>
  );
};