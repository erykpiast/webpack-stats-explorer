let logStats = (title, stats) => {
  Js.log(title);
  stats |> Stats.encode |> Js.log;
};

let logComp = (title, comp) => {
  Js.log(title);
  comp |> Compare.encode |> Js.log;
}

logStats("a", Data.a);
logStats("b", Data.b);
logStats("c", Data.c);
logStats("d", Data.d);
logStats("e", Data.e);

let ab = Compare.compare(Data.a, Data.b);
let bc = Compare.compare(Data.b, Data.c);
let cd = Compare.compare(Data.c, Data.d);
let de = Compare.compare(Data.d, Data.e);

logComp("a VS b", ab);
logComp("b VS c", bc);

ReactDOMRe.renderToElementWithId(<App comparisons=[ab, bc, cd, de] />, "app");
