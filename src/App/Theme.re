open Css;

module Color = {
  module Background = {
    let default = rgb(235, 235, 235);

    let button = rgb(224, 224, 224);
    let primaryButton = rgb(33, 150, 243);
  };

  module Border = {
    let default = rgb(158, 158, 158);
  };

  module Text = {
    let primary = rgb(0, 0, 0);
    let secondary = rgb(97, 97, 97);
    let contrast = rgb(255, 255, 255);
  };

  module Added = {
    let default = rgb(211, 47, 47);
    let background = rgb(255, 205, 216);
  };

  module Removed = {
    let default = rgb(56, 142, 60);
    let background = rgb(205, 255, 216);
  };

  module Modified = {
    let default = rgb(247, 202, 136);
  };

  module Intact = {
    let default = rgb(158, 158, 158);
  };

  module Shadow = {
    let default = rgba(0, 0, 0, 0.3);

    module Button = {
      let primary = rgba(0, 0, 0, 0.2);
      let secondary = rgba(0, 0, 0, 0.14);
      let tertiary = rgba(0, 0, 0, 0.12);
    };
  };
};

module Space = {
  module Raw = {
    let default = 8;
    let half = default / 2;
    let double = default * 2;
    let triple = default * 3;
    let quadruple = default * 4;
    let tenfold = default * 10;
    let hexfold = default * 16;
    let doublehexfold = hexfold * 2;
    let triplehexfold = hexfold * 3;
    let quadruplehexfold = hexfold * 4;
  };

  let default = `px(Raw.default);

  let half = `px(Raw.half);

  let double = `px(Raw.double);

  let triple = `px(Raw.triple);

  let quadruple = `px(Raw.quadruple);

  let tenfold = `px(Raw.tenfold);

  let hexfold = `px(Raw.hexfold);

  let doublehexfold = `px(Raw.doublehexfold);

  let triplehexfold = `px(Raw.triplehexfold);

  let quadruplehexfold = `px(Raw.quadruplehexfold);
};

module Size = {
  module Text = {
    let default = px(16);
    let big = px(28);
  };
};

let betterColor = rgb(205, 255, 216);
let changeColor = rgb(247, 202, 136);
let padding = `px(4);