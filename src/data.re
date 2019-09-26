let a = WebpackStats.decode([%raw {|require('../playground/enhanced/a.json')|}]);
let b = WebpackStats.decode([%raw {|require('../playground/enhanced/b.json')|}]);
let c = WebpackStats.decode([%raw {|require('./data/small/c.json')|}]);
let d = WebpackStats.decode([%raw {|require('./data/small/d.json')|}]);
let e = WebpackStats.decode([%raw {|require('./data/small/e.json')|}]);