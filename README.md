webpack-stats-explorer
======================

Tool for exploring webpack stats and comparing them between builds.

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
