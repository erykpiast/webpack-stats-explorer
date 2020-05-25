const autoprefixer = require('autoprefixer');
const WebpackEnhancedStatsPlugin = require('webpack-enhanced-stats-plugin');

module.exports = {
  entry: './src/index.js',
  devtool: 'source-map',
  module: {
    rules: [{
      test: /\.css$/,
      exclude: /(node_modules)/,
      use: [{
        loader: 'css-loader',
      }, {
        loader: 'postcss-loader',
        options: {
          plugins: [autoprefixer({ env: 'last 4 versions' })],
          sourceMap: true,
        }
      }]
    }, {
      loader: WebpackEnhancedStatsPlugin.loader
    }]
  },
  plugins: [
    new WebpackEnhancedStatsPlugin({
      filename: 'stats.json'
    })
  ]
};