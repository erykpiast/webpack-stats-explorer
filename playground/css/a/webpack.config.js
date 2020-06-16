const WebpackEnhancedStatsPlugin = require('webpack-enhanced-stats-plugin');

module.exports = {
  entry: './src/index.js',
  devtool: 'source-map',
  module: {
    rules: [{
      test: /\.css$/,
      exclude: /(node_modules)/,
      use: {
        loader: 'css-loader',
      }
    }, {
      loader: WebpackEnhancedStatsPlugin.loader
    }]
  },
  plugins: [new WebpackEnhancedStatsPlugin({
    filename: 'stats.json'
  })]
};