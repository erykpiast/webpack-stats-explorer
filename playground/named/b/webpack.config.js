const { NamedChunksPlugin } = require('webpack');

module.exports = {
  entry: './src/index.js',
  plugins: [
    new NamedChunksPlugin((chunk) => 'foobar')
  ]
};