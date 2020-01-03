const crypto = require('crypto');
const { NamedChunksPlugin } = require('webpack');

module.exports = {
  entry: './src/index.js',
  plugins: [
    new NamedChunksPlugin((chunk) => chunk.name || crypto
      .createHash('sha256')
      .update(`${chunk.id}_${Math.random()}`)
      .digest('hex')
      .slice(0, 8)
    )
  ],
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
