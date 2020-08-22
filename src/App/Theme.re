open Css;

module Color = {
  module Background = {
    let default = rgb(235, 235, 235);

    let button = rgb(224, 224, 224);

    let primaryButton = rgb(33, 150, 243);

    let dark = rgb(50, 50, 50);

    let selected = rgb(224, 224, 224);

    let reason = rgb(245, 245, 245);

    let danger = rgb(211, 47, 47);

    let bright = rgb(255, 255, 255);

    let code = rgb(245, 245, 245);
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
    let default = rgba(0, 0, 0, `num(0.3));

    module Button = {
      let primary = rgba(0, 0, 0, `num(0.2));
      let secondary = rgba(0, 0, 0, `num(0.14));
      let tertiary = rgba(0, 0, 0, `num(0.12));
    };
  };

  module Chart = {
    module Fill = {
      module Red = {
        let light = rgb(255, 235, 238);

        let normal = rgb(255, 205, 210);

        let dark = rgb(255, 138, 128);
      };

      module Green = {
        let light = rgb(200, 230, 201);
        let normal = rgb(165, 214, 167);
        let dark = rgb(129, 199, 132);
      };

      module Blue = {
        let light = rgb(187, 222, 251);

        let normal = rgb(144, 202, 249);

        let dark = rgb(100, 181, 246);
      };

      module Yellow = {
        let light = rgb(255, 249, 196);
        let normal = rgb(255, 245, 157);
        let dark = rgb(255, 241, 118);
      };
    };

    module Stroke = {
      module Red = {
        let light = rgb(211, 47, 47);

        let normal = rgb(198, 40, 40);

        let dark = rgb(183, 28, 28);
      };

      module Green = {
        let light = rgb(56, 142, 60);
        let normal = rgb(46, 125, 50);
        let dark = rgb(27, 94, 32);
      };

      module Blue = {
        let light = rgb(25, 118, 210);
        let normal = rgb(21, 101, 192);
        let dark = rgb(13, 71, 161);
      };

      module Yellow = {
        let light = rgb(251, 192, 45);
        let normal = rgb(249, 168, 37);
        let dark = rgb(245, 127, 23);
      };
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
    let octafold = default * 8;
    let tenfold = default * 10;
    let thirteenfold = default * 13;
    let hexteenfold = default * 16;
    let nineteenfold = default * 19;
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

  let octafold = `px(Raw.octafold);

  let tenfold = `px(Raw.tenfold);

  let thirteenfold = `px(Raw.thirteenfold);

  let hexteenfold = `px(Raw.hexteenfold);

  let nineteenfold = `px(Raw.nineteenfold);

  let doublehexteenfold = `px(Raw.doublehexteenfold);

  let triplehexteenfold = `px(Raw.triplehexteenfold);

  let quadruplehexteenfold = `px(Raw.quadruplehexteenfold);
};

module Size = {
  module Text = {
    let button = px(13);
    let default = px(16);
    let big = px(28);
  };

  module LineHeight = {
    let default = em(1.75);
  };

  module Border = {
    module Radius = {
      let default = Space.half;
    };
  };
};

module FontFamily = {
  let code = [
    `custom("Consolas"),
    `custom("Monaco"),
    `custom("Andale Mono"),
    `custom("Ubuntu Mono"),
    `monospace,
  ];
}

let betterColor = rgb(205, 255, 216);
let changeColor = rgb(247, 202, 136);
let padding = `px(4);