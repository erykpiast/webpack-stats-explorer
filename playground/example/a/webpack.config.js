const TerserPlugin = require('terser-webpack-plugin');
const WebpackEnhancedStatsPlugin = require('webpack-enhanced-stats-plugin');

module.exports = {
  entry: './src/app.js',
  devtool: 'source-map',
  module: {
    rules: [{
      test: /\.m?js$/,
      exclude: /(node_modules)/,
      use: {
        loader: 'babel-loader',
        options: {
          presets: ['@babel/preset-env'],
          plugins: [
            [
              "@babel/plugin-transform-runtime",
              {
                "regenerator": true,
                "helpers": false
              }
            ]
          ]
        }
      }
    }, {
      loader: WebpackEnhancedStatsPlugin.loader
    }]
  },
  optimization: {
    minimizer: [new TerserPlugin({
      sourceMap: true
    })],
  },
  plugins: [new WebpackEnhancedStatsPlugin({
    filename: 'stats.json'
  })]
};