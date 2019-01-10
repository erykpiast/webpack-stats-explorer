const HtmlWebpackPlugin = require('html-webpack-plugin')
const path = require('path');

const isProd = process.env.NODE_ENV === 'production';

module.exports = {
  entry: './src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: path.join(__dirname, 'build/'),
  },
  plugins: [new HtmlWebpackPlugin({ template: './src/index.html' })],
};
