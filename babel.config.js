module.exports = (api) => {
  const isTest = api.cache(() => !!process.env.TEST);

  return {
    presets: [
      ['@babel/preset-env', {
        modules: isTest ? 'cjs' : false,
        targets: isTest ? ({
          node: 11,
        }) : ({
          esmodules: true,
        })
      }]
    ],
  };
};
