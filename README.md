webpack-stats-explorer
======================

[![Build Status](https://travis-ci.org/erykpiast/webpack-stats-explorer.svg?branch=master)](https://travis-ci.org/erykpiast/webpack-stats-explorer)
[![dependencies Status](https://david-dm.org/erykpiast/webpack-stats-explorer/status.svg)](https://david-dm.org/erykpiast/webpack-stats-explorer)
[![Greenkeeper badge](https://badges.greenkeeper.io/erykpiast/webpack-stats-explorer.svg)](https://greenkeeper.io/)

Tool for exploring webpack stats and comparing them between builds.

## Demo

https://erykpiast.github.io/webpack-stats-explorer/

## Development

### Run Project

```sh
npm install
npm start
# in another tab
npm run webpack
```
After you see the webpack compilation succeed (the `npm run webpack` step), open up `http://localhost:8080` in the browser.

### Build for Production

```sh
npm run build
npm run webpack:production
```

This will replace the development artifact `build/bundle.js` for an optimized version.
