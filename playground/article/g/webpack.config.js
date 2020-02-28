const HtmlWebpackPlugin = require('html-webpack-plugin');
const MiniCssExtractPlugin = require('mini-css-extract-plugin');
const TerserPlugin = require('terser-webpack-plugin');
const path = require('path');
const WebpackEnhancedStatsPlugin = require('webpack-enhanced-stats-plugin');

module.exports = {
  entry: './src/index.js',
  devtool: 'source-map',
  resolve: {
    extensions: ['.js', '.jsx'],
  },
  module: {
    rules: [{
      test: /\.(js|jsx)$/,
      exclude: [path.join(__dirname, 'node_modules')],
      use: {
        loader: 'babel-loader',
        options: {
          presets: [
            '@babel/preset-env',
            [
              '@babel/preset-react',
              {
                'pragma': 'DOM.createElement',
              }
            ]
          ],
          plugins: [
            ['babel-plugin-transform-imports', {
              nanoutils: {
                transform: 'nanoutils/lib/${member}',
                preventFullImport: true
              }
            }]
          ]
        }
      }
    }, {
      test: /\.css$/,
      exclude: [path.join(__dirname, 'node_modules')],
      use: [
        MiniCssExtractPlugin.loader, {
          loader: 'css-loader',
          options: {
            modules: {
              mode: 'local',
              localIdentName: '[local]-[hash:base64:5]',
              context: path.resolve(__dirname, 'src'),
            }
          }
        }
      ]
    }, {
      test: /\.(html|ejs)$/,
      use: 'raw-loader'
    }, {
      loader: WebpackEnhancedStatsPlugin.loader
    }]
  },
  optimization: {
    minimizer: [new TerserPlugin({
      sourceMap: true
    })],
  },
  plugins: [
    new HtmlWebpackPlugin(),
    new MiniCssExtractPlugin(),
    new WebpackEnhancedStatsPlugin({
      filename: 'stats.json'
    }),
  ]
};