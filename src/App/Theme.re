open Css;

module Color = {
  module Border = {
    let default = rgb(64, 64, 64);
  };

  module Added = {
    let default = rgb(205, 255, 216);
  };

  module Removed = {
    let default = rgb(205, 255, 216);
  };

  module Changed = {
    let default = rgb(247, 202, 136);
  };
};

module Space = {
  let default = px(8);
};

let worseColor = rgb(255, 220, 224);

let betterColor = rgb(205, 255, 216);
let changeColor = rgb(247, 202, 136);

let padding = px(4);