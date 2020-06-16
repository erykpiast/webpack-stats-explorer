const autoprefixer = require('autoprefixer');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');
const OptimizeCSSAssetsPlugin = require('optimize-css-assets-webpack-plugin');
const TerserJSPlugin = require('terser-webpack-plugin');
const WebpackEnhancedStatsPlugin = require('webpack-enhanced-stats-plugin');

module.exports = {
  entry: './src/index.js',
  devtool: 'source-map',
  module: {
    rules: [{
      test: /\.css$/,
      exclude: /(node_modules)/,
      use: [{
        loader: MiniCssExtractPlugin.loader,
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
          plugins: [autoprefixer({ env: 'last 4 versions' })],
          sourceMap: true,
        }
      }]
    }, {
      loader: WebpackEnhancedStatsPlugin.loader
    }]
  },
  optimization: {
    minimizer: [new TerserJSPlugin({}), new OptimizeCSSAssetsPlugin({})],
  },
  plugins: [
    new MiniCssExtractPlugin(),
    new WebpackEnhancedStatsPlugin({
      filename: 'stats.json'
    })
  ]
};