open Css;

module Color = {
  module Background = {
    let default = rgb(235, 235, 235);

    let button = rgb(224, 224, 224);

    let primaryButton = rgb(33, 150, 243);

    let dark = rgb(50, 50, 50);

    let selected = rgb(224, 224, 224);

    let danger = rgb(211, 47, 47);

    let bright = rgb(255, 255, 255);
  };

  module Border = {
    let default = rgb(158, 158, 158);

    let accent = rgb(25, 118, 210);
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
    let fivefold = default * 5;
    let hexfold = default * 6;
    let sevenfold = default * 7;
    let tenfold = default * 10;
    let hexteenfold = default * 16;
    let doublehexteenfold = hexteenfold * 2;
    let triplehexteenfold = hexteenfold * 3;
    let quadruplehexteenfold = hexteenfold * 4;
  };

  let default = `px(Raw.default);

  let half = `px(Raw.half);

  let double = `px(Raw.double);

  let triple = `px(Raw.triple);

  let quadruple = `px(Raw.quadruple);

  let fivefold = `px(Raw.fivefold);

  let hexfold = `px(Raw.hexfold);

  let sevenfold = `px(Raw.sevenfold);

  let tenfold = `px(Raw.tenfold);

  let hexteenfold = `px(Raw.hexteenfold);

  let doublehexteenfold = `px(Raw.doublehexteenfold);

  let triplehexteenfold = `px(Raw.triplehexteenfold);

  let quadruplehexteenfold = `px(Raw.quadruplehexteenfold);
};

module Size = {
  module Text = {
    let default = px(16);
    let big = px(28);
  };

  module Border = {
    module Radius = {
      let default = Space.half;
    };
  };
};

let betterColor = rgb(205, 255, 216);
let changeColor = rgb(247, 202, 136);
let padding = `px(4);