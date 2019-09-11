const HtmlWebpackPlugin = require('html-webpack-plugin');
const {
  BundleAnalyzerPlugin
} = require('webpack-bundle-analyzer');
const path = require('path');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: path.join(__dirname, 'dist/'),
  },
  plugins: [
    new HtmlWebpackPlugin({
      template: './src/index.html'
    }),
    new BundleAnalyzerPlugin({
      analyzerMode: 'static',
      openAnalyzer: false,
      generateStatsFile: true,
    }),
  ],
};