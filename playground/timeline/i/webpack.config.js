const webpack = require('webpack');

module.exports = {
  entry: './src/index.js',
  plugins: [
    new webpack.optimize.LimitChunkCountPlugin({
      maxChunks: 1
    })
  ]
};