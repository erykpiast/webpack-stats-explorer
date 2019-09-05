const TerserPlugin = require('terser-webpack-plugin');
const WebpackEnhancedStatsPlugin = require('webpack-enhanced-stats-plugin');

module.exports = {
  entry: './src/index.js',
  devtool: 'source-map',
  optimization: {
    minimizer: [new TerserPlugin({
      sourceMap: true
    })],
  },
  plugins: [new WebpackEnhancedStatsPlugin({
    filename: 'stats.json'
  })]
};