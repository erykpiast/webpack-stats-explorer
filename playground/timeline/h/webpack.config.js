module.exports = {
  entry: './src/index.js',
  optimization: {
    splitChunks: {
      cacheGroups: {
        common: {
          test(mod) {
            return mod.resource.endsWith('common.js');
          },
          priority: 10,
          enforce: true,
          chunks: 'all'
        },
      }
    }
  }
};