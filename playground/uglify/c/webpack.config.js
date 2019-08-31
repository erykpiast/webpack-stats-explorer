const TerserPlugin = require('terser-webpack-plugin');

module.exports = {
    entry: './src/index.js',
    optimization: {
        minimizer: [new TerserPlugin()],
    },
};