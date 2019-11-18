(function main(params) {
  import('./foo').then(foo => foo());
  import('./bar').then(bar => bar());
})();