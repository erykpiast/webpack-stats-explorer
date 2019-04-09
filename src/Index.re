let logStats = (title, stats) => {
  Js.log(title);
  stats |> Stats.encode |> Js.log;
};

let logComp = (title, comp) => {
  Js.log(title);
  comp |> Compare.encode |> Js.log;
};

logStats("a", Data.a);
logStats("b", Data.b);
logStats("c", Data.c);
logStats("d", Data.d);
logStats("e", Data.e);

let ab = Compare.make(Data.a, Data.b);
let bc = Compare.make(Data.b, Data.c);
let cd = Compare.make(Data.c, Data.d);
let de = Compare.make(Data.d, Data.e);

logComp("a VS b", ab);
logComp("b VS c", bc);
logComp("c VS d", cd);
logComp("d VS e", de);

ReactDOMRe.renderToElementWithId(
  <App comparisons=[ab, bc, cd, de] />,
  "app",
);