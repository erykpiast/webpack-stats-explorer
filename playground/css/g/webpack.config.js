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
        loader: 'style-loader',
        options: {
          esModule: true,
        }
      }, {
        loader: 'css-loader',
        options: {
          modules: {
            mode: 'local',
            localIdentName: '[hash:base64:5]',
          },
          esModule: true,
          sourceMap: true,
        }
      }, {
        loader: 'postcss-loader',
        options: {
          postcssOptions: {
            plugins: [autoprefixer({ env: 'last 4 versions' })],
          },
          sourceMap: true,
        }
      }]
    }, {
      loader: WebpackEnhancedStatsPlugin.loader
    }]
  },
  plugins: [new WebpackEnhancedStatsPlugin({
    filename: 'stats.json'
  })]
};