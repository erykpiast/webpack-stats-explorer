let decodeStats = (json) => {
  let decoded = json |> Json.parseOrRaise |> Stats.decode

  /* Js.log("=====================================");
  Js.log(("errors", decoded.errors));
  Js.log(("warnings", decoded.warnings));
  Js.log(("version", decoded.version));
  Js.log(("hash", decoded.hash));
  Js.log(("time", decoded.time));
  Js.log(("builtAt", decoded.builtAt));
  Js.log(("outputPath", decoded.outputPath));
  Js.log(("assetsByChunkName", decoded.assetsByChunkName));
  Js.log(("assets", decoded.assets));
  Js.log(("filteredAssets", decoded.filteredAssets));
  Js.log(("entrypoints", decoded.entrypoints));
  Js.log(("modules", decoded.modules));
  Js.log(("chunks", decoded.chunks)); */

  decoded;
};

let a = decodeStats({| {
  "errors": [],
  "warnings": [
    "configuration\nThe 'mode' option has not been set, webpack will fallback to 'production' for this value. Set 'mode' option to 'development' or 'production' to enable defaults for each environment.\nYou can also set it to 'none' to disable any default behavior. Learn more: https://webpack.js.org/concepts/mode/"
  ],
  "version": "4.28.3",
  "hash": "94a974c5707ada6be497",
  "time": 333,
  "builtAt": 1546890225179,
  "publicPath": "",
  "outputPath": "/Users/eryk.napierala/Projects/webpack-stats-playground/dist",
  "assetsByChunkName": {
    "main": "main.js"
  },
  "assets": [{
    "name": "main.js",
    "size": 983,
    "chunks": [
      0
    ],
    "chunkNames": [
      "main"
    ],
    "emitted": true
  }],
  "filteredAssets": 0,
  "entrypoints": {
    "main": {
      "chunks": [
        0
      ],
      "assets": [
        "main.js"
      ],
      "children": {},
      "childAssets": {}
    }
  },
  "namedChunkGroups": {
    "main": {
      "chunks": [
        0
      ],
      "assets": [
        "main.js"
      ],
      "children": {},
      "childAssets": {}
    }
  },
  "children": [],
  "modules": [{
    "id": 0,
    "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js 9e2835302c0dd7617bb31a4eb099dd63",
    "name": "./src/index.js + 3 modules",
    "index": 0,
    "index2": 3,
    "size": 175,
    "cacheable": true,
    "built": true,
    "optional": false,
    "prefetched": false,
    "chunks": [
      0
    ],
    "issuer": null,
    "issuerId": null,
    "issuerName": null,
    "issuerPath": null,
    "failed": false,
    "errors": 0,
    "warnings": 0,
    "assets": [],
    "reasons": [{
      "moduleId": null,
      "moduleIdentifier": null,
      "module": null,
      "moduleName": null,
      "type": "single entry",
      "userRequest": "./src",
      "loc": "main"
    }],
    "usedExports": true,
    "providedExports": [],
    "optimizationBailout": [],
    "depth": 0,
    "modules": [{
        "id": null,
        "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
        "name": "./src/index.js",
        "index": 0,
        "index2": 3,
        "size": 59,
        "cacheable": true,
        "built": true,
        "optional": false,
        "prefetched": false,
        "chunks": [],
        "issuer": null,
        "issuerId": null,
        "issuerName": null,
        "issuerPath": null,
        "profile": {
          "factory": 42,
          "building": 11
        },
        "failed": false,
        "errors": 0,
        "warnings": 0,
        "assets": [],
        "reasons": [{
          "moduleId": null,
          "moduleIdentifier": null,
          "module": null,
          "moduleName": null,
          "type": "single entry",
          "userRequest": "./src",
          "loc": "main"
        }],
        "usedExports": true,
        "providedExports": [],
        "optimizationBailout": [
          "ModuleConcatenation bailout: Module is an entry point"
        ],
        "depth": 0,
        "source": "import a from './a';\nimport c from './c';\n\nalert(...a(c));\n"
      },
      {
        "id": null,
        "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/c.js",
        "name": "./src/c.js",
        "index": 3,
        "index2": 1,
        "size": 20,
        "cacheable": true,
        "built": true,
        "optional": false,
        "prefetched": false,
        "chunks": [],
        "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
        "issuerId": null,
        "issuerName": "./src/index.js",
        "issuerPath": [{
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
          "name": "./src/index.js",
          "profile": {
            "factory": 42,
            "building": 11
          }
        }],
        "profile": {
          "factory": 3,
          "building": 4,
          "dependencies": 0
        },
        "failed": false,
        "errors": 0,
        "warnings": 0,
        "assets": [],
        "reasons": [{
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
            "module": "./src/index.js",
            "moduleName": "./src/index.js",
            "type": "harmony side effect evaluation",
            "userRequest": "./c",
            "loc": "2:0-20"
          },
          {
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
            "module": "./src/a.js",
            "moduleName": "./src/a.js",
            "type": "harmony side effect evaluation",
            "userRequest": "./c",
            "loc": "2:0-20"
          },
          {
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
            "module": "./src/index.js",
            "moduleName": "./src/index.js",
            "type": "harmony import specifier",
            "userRequest": "./c",
            "loc": "4:11-12"
          },
          {
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
            "module": "./src/a.js",
            "moduleName": "./src/a.js",
            "type": "harmony import specifier",
            "userRequest": "./c",
            "loc": "4:29-30"
          }
        ],
        "usedExports": [
          "default"
        ],
        "providedExports": [
          "default"
        ],
        "optimizationBailout": [],
        "depth": 1,
        "source": "export default 'c';\n"
      },
      {
        "id": null,
        "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
        "name": "./src/a.js",
        "index": 1,
        "index2": 2,
        "size": 76,
        "cacheable": true,
        "built": true,
        "optional": false,
        "prefetched": false,
        "chunks": [],
        "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
        "issuerId": null,
        "issuerName": "./src/index.js",
        "issuerPath": [{
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
          "name": "./src/index.js",
          "profile": {
            "factory": 42,
            "building": 11
          }
        }],
        "profile": {
          "factory": 3,
          "building": 4,
          "dependencies": 0
        },
        "failed": false,
        "errors": 0,
        "warnings": 0,
        "assets": [],
        "reasons": [{
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
            "module": "./src/index.js",
            "moduleName": "./src/index.js",
            "type": "harmony side effect evaluation",
            "userRequest": "./a",
            "loc": "1:0-20"
          },
          {
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
            "module": "./src/index.js",
            "moduleName": "./src/index.js",
            "type": "harmony import specifier",
            "userRequest": "./a",
            "loc": "4:9-10"
          }
        ],
        "usedExports": [
          "default"
        ],
        "providedExports": [
          "default"
        ],
        "optimizationBailout": [],
        "depth": 1,
        "source": "import b from './b';\nimport c from './c';\n\nexport default (a) => [a, b, c];\n"
      },
      {
        "id": null,
        "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/b.js",
        "name": "./src/b.js",
        "index": 2,
        "index2": 0,
        "size": 20,
        "cacheable": true,
        "built": true,
        "optional": false,
        "prefetched": false,
        "chunks": [],
        "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
        "issuerId": null,
        "issuerName": "./src/a.js",
        "issuerPath": [{
            "id": null,
            "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
            "name": "./src/index.js",
            "profile": {
              "factory": 42,
              "building": 11
            }
          },
          {
            "id": null,
            "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
            "name": "./src/a.js",
            "profile": {
              "factory": 3,
              "building": 4,
              "dependencies": 0
            }
          }
        ],
        "profile": {
          "factory": 2,
          "building": 0
        },
        "failed": false,
        "errors": 0,
        "warnings": 0,
        "assets": [],
        "reasons": [{
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
            "module": "./src/a.js",
            "moduleName": "./src/a.js",
            "type": "harmony side effect evaluation",
            "userRequest": "./b",
            "loc": "1:0-20"
          },
          {
            "moduleId": null,
            "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
            "module": "./src/a.js",
            "moduleName": "./src/a.js",
            "type": "harmony import specifier",
            "userRequest": "./b",
            "loc": "4:26-27"
          }
        ],
        "usedExports": [
          "default"
        ],
        "providedExports": [
          "default"
        ],
        "optimizationBailout": [],
        "depth": 2,
        "source": "export default 'b';\n"
      }
    ],
    "filteredModules": 0
  }],
  "chunks": [
    {
      "id": 0,
      "rendered": true,
      "initial": true,
      "entry": true,
      "size": 175,
      "names": [
        "main"
      ],
      "files": [
        "main.js"
      ],
      "hash": "be29e5bde47bfbc6cf76",
      "siblings": [],
      "parents": [],
      "children": [],
      "childrenByOrder": {},
      "modules": [
        {
          "id": 0,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js 9e2835302c0dd7617bb31a4eb099dd63",
          "name": "./src/index.js + 3 modules",
          "index": 0,
          "index2": 3,
          "size": 175,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            0
          ],
          "issuer": null,
          "issuerId": null,
          "issuerName": null,
          "issuerPath": null,
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": null,
              "module": null,
              "moduleName": null,
              "type": "single entry",
              "userRequest": "./src",
              "loc": "main"
            }
          ],
          "usedExports": true,
          "providedExports": [],
          "optimizationBailout": [],
          "depth": 0,
          "modules": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
              "name": "./src/index.js",
              "index": 0,
              "index2": 3,
              "size": 59,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": null,
              "issuerId": null,
              "issuerName": null,
              "issuerPath": null,
              "profile": {
                "factory": 42,
                "building": 11
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": null,
                  "module": null,
                  "moduleName": null,
                  "type": "single entry",
                  "userRequest": "./src",
                  "loc": "main"
                }
              ],
              "usedExports": true,
              "providedExports": [],
              "optimizationBailout": [
                "ModuleConcatenation bailout: Module is an entry point"
              ],
              "depth": 0,
              "source": "import a from './a';\nimport c from './c';\n\nalert(...a(c));\n"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/c.js",
              "name": "./src/c.js",
              "index": 3,
              "index2": 1,
              "size": 20,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
              "issuerId": null,
              "issuerName": "./src/index.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
                  "name": "./src/index.js",
                  "profile": {
                    "factory": 42,
                    "building": 11
                  }
                }
              ],
              "profile": {
                "factory": 3,
                "building": 4,
                "dependencies": 0
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
                  "module": "./src/index.js",
                  "moduleName": "./src/index.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./c",
                  "loc": "2:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "module": "./src/a.js",
                  "moduleName": "./src/a.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./c",
                  "loc": "2:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
                  "module": "./src/index.js",
                  "moduleName": "./src/index.js",
                  "type": "harmony import specifier",
                  "userRequest": "./c",
                  "loc": "4:11-12"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "module": "./src/a.js",
                  "moduleName": "./src/a.js",
                  "type": "harmony import specifier",
                  "userRequest": "./c",
                  "loc": "4:29-30"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 1,
              "source": "export default 'c';\n"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "name": "./src/a.js",
              "index": 1,
              "index2": 2,
              "size": 76,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
              "issuerId": null,
              "issuerName": "./src/index.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
                  "name": "./src/index.js",
                  "profile": {
                    "factory": 42,
                    "building": 11
                  }
                }
              ],
              "profile": {
                "factory": 3,
                "building": 4,
                "dependencies": 0
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
                  "module": "./src/index.js",
                  "moduleName": "./src/index.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./a",
                  "loc": "1:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
                  "module": "./src/index.js",
                  "moduleName": "./src/index.js",
                  "type": "harmony import specifier",
                  "userRequest": "./a",
                  "loc": "4:9-10"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 1,
              "source": "import b from './b';\nimport c from './c';\n\nexport default (a) => [a, b, c];\n"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/b.js",
              "name": "./src/b.js",
              "index": 2,
              "index2": 0,
              "size": 20,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "issuerId": null,
              "issuerName": "./src/a.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index.js",
                  "name": "./src/index.js",
                  "profile": {
                    "factory": 42,
                    "building": 11
                  }
                },
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "name": "./src/a.js",
                  "profile": {
                    "factory": 3,
                    "building": 4,
                    "dependencies": 0
                  }
                }
              ],
              "profile": {
                "factory": 2,
                "building": 0
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "module": "./src/a.js",
                  "moduleName": "./src/a.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./b",
                  "loc": "1:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "module": "./src/a.js",
                  "moduleName": "./src/a.js",
                  "type": "harmony import specifier",
                  "userRequest": "./b",
                  "loc": "4:26-27"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 2,
              "source": "export default 'b';\n"
            }
          ],
          "filteredModules": 0
        }
      ],
      "filteredModules": 0,
      "origins": [
        {
          "module": "",
          "moduleIdentifier": "",
          "moduleName": "",
          "loc": "main",
          "request": "./src",
          "reasons": []
        }
      ]
    }
  ]
} |});

let b = decodeStats({| {
  "errors": [],
  "warnings": [
    "configuration\nThe 'mode' option has not been set, webpack will fallback to 'production' for this value. Set 'mode' option to 'development' or 'production' to enable defaults for each environment.\nYou can also set it to 'none' to disable any default behavior. Learn more: https://webpack.js.org/concepts/mode/"
  ],
  "version": "4.28.4",
  "hash": "a01a9f4c9a7bfc30437f",
  "time": 658,
  "builtAt": 1547214442992,
  "publicPath": "",
  "outputPath": "/Users/eryk.napierala/Projects/webpack-stats-playground/dist",
  "assetsByChunkName": {
    "index1": "index1.js",
    "index2": "index2.js"
  },
  "assets": [
    {
      "name": "2.js",
      "size": 113,
      "chunks": [
        2
      ],
      "chunkNames": [],
      "emitted": true
    },
    {
      "name": "index1.js",
      "size": 2193,
      "chunks": [
        0
      ],
      "chunkNames": [
        "index1"
      ],
      "emitted": true
    },
    {
      "name": "index2.js",
      "size": 1086,
      "chunks": [
        1
      ],
      "chunkNames": [
        "index2"
      ],
      "emitted": true
    }
  ],
  "filteredAssets": 0,
  "entrypoints": {
    "index1": {
      "chunks": [
        0
      ],
      "assets": [
        "index1.js"
      ],
      "children": {},
      "childAssets": {}
    },
    "index2": {
      "chunks": [
        1
      ],
      "assets": [
        "index2.js"
      ],
      "children": {},
      "childAssets": {}
    }
  },
  "namedChunkGroups": {
    "index1": {
      "chunks": [
        0
      ],
      "assets": [
        "index1.js"
      ],
      "children": {},
      "childAssets": {}
    },
    "index2": {
      "chunks": [
        1
      ],
      "assets": [
        "index2.js"
      ],
      "children": {},
      "childAssets": {}
    }
  },
  "chunks": [
    {
      "id": 0,
      "rendered": true,
      "initial": true,
      "entry": true,
      "size": 220,
      "names": [
        "index1"
      ],
      "files": [
        "index1.js"
      ],
      "hash": "77e3a41b2477cea497c5",
      "siblings": [],
      "parents": [],
      "children": [
        2
      ],
      "childrenByOrder": {},
      "modules": [
        {
          "id": 0,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/b.js",
          "name": "./src/b.js",
          "index": 2,
          "index2": 0,
          "size": 20,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            0,
            1
          ],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "issuerId": 1,
          "issuerName": "./src/d.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 76,
                "building": 19
              }
            },
            {
              "id": 1,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "name": "./src/d.js",
              "profile": {
                "factory": 7,
                "building": 9,
                "dependencies": 2
              }
            }
          ],
          "profile": {
            "factory": 6,
            "building": 1
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": 1,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "module": "./src/d.js",
              "moduleName": "./src/d.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./b",
              "loc": "1:0-20"
            },
            {
              "moduleId": 1,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "module": "./src/d.js",
              "moduleName": "./src/d.js",
              "type": "harmony import specifier",
              "userRequest": "./b",
              "loc": "3:26-27"
            },
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony side effect evaluation",
              "userRequest": "./b",
              "loc": "1:0-20"
            },
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony import specifier",
              "userRequest": "./b",
              "loc": "3:50-51"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 2,
          "source": "export default 'b';\n"
        },
        {
          "id": 1,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "name": "./src/d.js",
          "index": 3,
          "index2": 2,
          "size": 51,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            0,
            1
          ],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "issuerId": null,
          "issuerName": "./src/index1.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 76,
                "building": 19
              }
            }
          ],
          "profile": {
            "factory": 7,
            "building": 9,
            "dependencies": 2
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony side effect evaluation",
              "userRequest": "./d",
              "loc": "2:0-20"
            },
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony import specifier",
              "userRequest": "./d",
              "loc": "4:11-12"
            },
            {
              "moduleId": 3,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
              "module": "./src/index2.js + 1 modules",
              "moduleName": "./src/index2.js + 1 modules",
              "type": "harmony side effect evaluation",
              "userRequest": "./d",
              "loc": "1:0-20"
            },
            {
              "moduleId": 3,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
              "module": "./src/index2.js + 1 modules",
              "moduleName": "./src/index2.js + 1 modules",
              "type": "harmony import specifier",
              "userRequest": "./d",
              "loc": "4:9-10"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 1,
          "source": "import b from './b';\n\nexport default (e) => [e, b];"
        },
        {
          "id": 2,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
          "name": "./src/index1.js + 1 modules",
          "index": 0,
          "index2": 3,
          "size": 149,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            0
          ],
          "issuer": null,
          "issuerId": null,
          "issuerName": null,
          "issuerPath": null,
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": null,
              "module": null,
              "moduleName": null,
              "type": "single entry",
              "userRequest": "./src/index1.js",
              "loc": "index1"
            }
          ],
          "usedExports": true,
          "providedExports": [],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Cannot concat with ./src/b.js",
            "ModuleConcatenation bailout: Cannot concat with ./src/d.js"
          ],
          "depth": 0,
          "modules": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "index": 0,
              "index2": 3,
              "size": 59,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": null,
              "issuerId": null,
              "issuerName": null,
              "issuerPath": null,
              "profile": {
                "factory": 76,
                "building": 19
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": null,
                  "module": null,
                  "moduleName": null,
                  "type": "single entry",
                  "userRequest": "./src/index1.js",
                  "loc": "index1"
                }
              ],
              "usedExports": true,
              "providedExports": [],
              "optimizationBailout": [
                "ModuleConcatenation bailout: Module is an entry point"
              ],
              "depth": 0,
              "source": "import a from './a';\nimport d from './d';\n\nalert(...a(d));\n"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "name": "./src/a.js",
              "index": 1,
              "index2": 1,
              "size": 80,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "issuerId": null,
              "issuerName": "./src/index1.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "name": "./src/index1.js",
                  "profile": {
                    "factory": 76,
                    "building": 19
                  }
                }
              ],
              "profile": {
                "factory": 7,
                "building": 9,
                "dependencies": 2
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "module": "./src/index1.js",
                  "moduleName": "./src/index1.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./a",
                  "loc": "1:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "module": "./src/index1.js",
                  "moduleName": "./src/index1.js",
                  "type": "harmony import specifier",
                  "userRequest": "./a",
                  "loc": "4:9-10"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 1,
              "source": "import b from './b';\n\nexport default (a) => import('./c').then(c => [a, b, c]);\n"
            }
          ],
          "filteredModules": 0
        }
      ],
      "filteredModules": 0,
      "origins": [
        {
          "module": "",
          "moduleIdentifier": "",
          "moduleName": "",
          "loc": "index1",
          "request": "./src/index1.js",
          "reasons": []
        }
      ]
    },
    {
      "id": 1,
      "rendered": true,
      "initial": true,
      "entry": true,
      "size": 155,
      "names": [
        "index2"
      ],
      "files": [
        "index2.js"
      ],
      "hash": "da9a00699f1196f47e48",
      "siblings": [],
      "parents": [],
      "children": [],
      "childrenByOrder": {},
      "modules": [
        {
          "id": 0,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/b.js",
          "name": "./src/b.js",
          "index": 2,
          "index2": 0,
          "size": 20,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            0,
            1
          ],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "issuerId": 1,
          "issuerName": "./src/d.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 76,
                "building": 19
              }
            },
            {
              "id": 1,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "name": "./src/d.js",
              "profile": {
                "factory": 7,
                "building": 9,
                "dependencies": 2
              }
            }
          ],
          "profile": {
            "factory": 6,
            "building": 1
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": 1,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "module": "./src/d.js",
              "moduleName": "./src/d.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./b",
              "loc": "1:0-20"
            },
            {
              "moduleId": 1,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "module": "./src/d.js",
              "moduleName": "./src/d.js",
              "type": "harmony import specifier",
              "userRequest": "./b",
              "loc": "3:26-27"
            },
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony side effect evaluation",
              "userRequest": "./b",
              "loc": "1:0-20"
            },
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony import specifier",
              "userRequest": "./b",
              "loc": "3:50-51"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 2,
          "source": "export default 'b';\n"
        },
        {
          "id": 1,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "name": "./src/d.js",
          "index": 3,
          "index2": 2,
          "size": 51,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            0,
            1
          ],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "issuerId": null,
          "issuerName": "./src/index1.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 76,
                "building": 19
              }
            }
          ],
          "profile": {
            "factory": 7,
            "building": 9,
            "dependencies": 2
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony side effect evaluation",
              "userRequest": "./d",
              "loc": "2:0-20"
            },
            {
              "moduleId": 2,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
              "module": "./src/index1.js + 1 modules",
              "moduleName": "./src/index1.js + 1 modules",
              "type": "harmony import specifier",
              "userRequest": "./d",
              "loc": "4:11-12"
            },
            {
              "moduleId": 3,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
              "module": "./src/index2.js + 1 modules",
              "moduleName": "./src/index2.js + 1 modules",
              "type": "harmony side effect evaluation",
              "userRequest": "./d",
              "loc": "1:0-20"
            },
            {
              "moduleId": 3,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
              "module": "./src/index2.js + 1 modules",
              "moduleName": "./src/index2.js + 1 modules",
              "type": "harmony import specifier",
              "userRequest": "./d",
              "loc": "4:9-10"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 1,
          "source": "import b from './b';\n\nexport default (e) => [e, b];"
        },
        {
          "id": 3,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
          "name": "./src/index2.js + 1 modules",
          "index": 4,
          "index2": 5,
          "size": 84,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            1
          ],
          "issuer": null,
          "issuerId": null,
          "issuerName": null,
          "issuerPath": null,
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": null,
              "module": null,
              "moduleName": null,
              "type": "single entry",
              "userRequest": "./src/index2.js",
              "loc": "index2"
            }
          ],
          "usedExports": true,
          "providedExports": [],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Cannot concat with ./src/d.js"
          ],
          "depth": 0,
          "modules": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
              "name": "./src/index2.js",
              "index": 4,
              "index2": 5,
              "size": 59,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": null,
              "issuerId": null,
              "issuerName": null,
              "issuerPath": null,
              "profile": {
                "factory": 65,
                "building": 20,
                "dependencies": 4
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": null,
                  "module": null,
                  "moduleName": null,
                  "type": "single entry",
                  "userRequest": "./src/index2.js",
                  "loc": "index2"
                }
              ],
              "usedExports": true,
              "providedExports": [],
              "optimizationBailout": [
                "ModuleConcatenation bailout: Module is an entry point"
              ],
              "depth": 0,
              "source": "import d from './d';\nimport e from './e';\n\nalert(...d(e));\n"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/e.js",
              "name": "./src/e.js",
              "index": 5,
              "index2": 4,
              "size": 20,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
              "issuerId": null,
              "issuerName": "./src/index2.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
                  "name": "./src/index2.js",
                  "profile": {
                    "factory": 65,
                    "building": 20,
                    "dependencies": 4
                  }
                }
              ],
              "profile": {
                "factory": 4,
                "building": 5
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
                  "module": "./src/index2.js",
                  "moduleName": "./src/index2.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./e",
                  "loc": "2:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
                  "module": "./src/index2.js",
                  "moduleName": "./src/index2.js",
                  "type": "harmony import specifier",
                  "userRequest": "./e",
                  "loc": "4:11-12"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 1,
              "source": "export default 'e';\n"
            }
          ],
          "filteredModules": 0
        }
      ],
      "filteredModules": 0,
      "origins": [
        {
          "module": "",
          "moduleIdentifier": "",
          "moduleName": "",
          "loc": "index2",
          "request": "./src/index2.js",
          "reasons": []
        }
      ]
    },
    {
      "id": 2,
      "rendered": true,
      "initial": false,
      "entry": false,
      "size": 20,
      "names": [],
      "files": [
        "2.js"
      ],
      "hash": "82d605743554801a24d7",
      "siblings": [],
      "parents": [
        0
      ],
      "children": [],
      "childrenByOrder": {},
      "modules": [
        {
          "id": 4,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/c.js",
          "name": "./src/c.js",
          "index": 6,
          "index2": 6,
          "size": 20,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            2
          ],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "issuerId": null,
          "issuerName": "./src/a.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 76,
                "building": 19
              }
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "name": "./src/a.js",
              "profile": {
                "factory": 7,
                "building": 9,
                "dependencies": 2
              }
            }
          ],
          "profile": {
            "factory": 2,
            "building": 1
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "module": "./src/a.js",
              "moduleName": "./src/a.js",
              "type": "import()",
              "userRequest": "./c",
              "loc": "3:22-35"
            }
          ],
          "usedExports": true,
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Module is referenced from these modules with unsupported syntax: ./src/a.js (referenced with import())"
          ],
          "depth": 2,
          "source": "export default 'c';\n"
        }
      ],
      "filteredModules": 0,
      "origins": [
        {
          "moduleId": null,
          "module": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "moduleName": "./src/a.js",
          "loc": "3:22-35",
          "request": "./c",
          "reasons": []
        }
      ]
    }
  ],
  "modules": [
    {
      "id": 0,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/b.js",
      "name": "./src/b.js",
      "index": 2,
      "index2": 0,
      "size": 20,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        0,
        1
      ],
      "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
      "issuerId": 1,
      "issuerName": "./src/d.js",
      "issuerPath": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "name": "./src/index1.js",
          "profile": {
            "factory": 76,
            "building": 19
          }
        },
        {
          "id": 1,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "name": "./src/d.js",
          "profile": {
            "factory": 7,
            "building": 9,
            "dependencies": 2
          }
        }
      ],
      "profile": {
        "factory": 6,
        "building": 1
      },
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": 1,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "module": "./src/d.js",
          "moduleName": "./src/d.js",
          "type": "harmony side effect evaluation",
          "userRequest": "./b",
          "loc": "1:0-20"
        },
        {
          "moduleId": 1,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "module": "./src/d.js",
          "moduleName": "./src/d.js",
          "type": "harmony import specifier",
          "userRequest": "./b",
          "loc": "3:26-27"
        },
        {
          "moduleId": 2,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
          "module": "./src/index1.js + 1 modules",
          "moduleName": "./src/index1.js + 1 modules",
          "type": "harmony side effect evaluation",
          "userRequest": "./b",
          "loc": "1:0-20"
        },
        {
          "moduleId": 2,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
          "module": "./src/index1.js + 1 modules",
          "moduleName": "./src/index1.js + 1 modules",
          "type": "harmony import specifier",
          "userRequest": "./b",
          "loc": "3:50-51"
        }
      ],
      "usedExports": [
        "default"
      ],
      "providedExports": [
        "default"
      ],
      "optimizationBailout": [],
      "depth": 2,
      "source": "export default 'b';\n"
    },
    {
      "id": 1,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
      "name": "./src/d.js",
      "index": 3,
      "index2": 2,
      "size": 51,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        0,
        1
      ],
      "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
      "issuerId": null,
      "issuerName": "./src/index1.js",
      "issuerPath": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "name": "./src/index1.js",
          "profile": {
            "factory": 76,
            "building": 19
          }
        }
      ],
      "profile": {
        "factory": 7,
        "building": 9,
        "dependencies": 2
      },
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": 2,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
          "module": "./src/index1.js + 1 modules",
          "moduleName": "./src/index1.js + 1 modules",
          "type": "harmony side effect evaluation",
          "userRequest": "./d",
          "loc": "2:0-20"
        },
        {
          "moduleId": 2,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
          "module": "./src/index1.js + 1 modules",
          "moduleName": "./src/index1.js + 1 modules",
          "type": "harmony import specifier",
          "userRequest": "./d",
          "loc": "4:11-12"
        },
        {
          "moduleId": 3,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
          "module": "./src/index2.js + 1 modules",
          "moduleName": "./src/index2.js + 1 modules",
          "type": "harmony side effect evaluation",
          "userRequest": "./d",
          "loc": "1:0-20"
        },
        {
          "moduleId": 3,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
          "module": "./src/index2.js + 1 modules",
          "moduleName": "./src/index2.js + 1 modules",
          "type": "harmony import specifier",
          "userRequest": "./d",
          "loc": "4:9-10"
        }
      ],
      "usedExports": [
        "default"
      ],
      "providedExports": [
        "default"
      ],
      "optimizationBailout": [],
      "depth": 1,
      "source": "import b from './b';\n\nexport default (e) => [e, b];"
    },
    {
      "id": 2,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js ecf410ec33a940834380e3ceab7d13cb",
      "name": "./src/index1.js + 1 modules",
      "index": 0,
      "index2": 3,
      "size": 149,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        0
      ],
      "issuer": null,
      "issuerId": null,
      "issuerName": null,
      "issuerPath": null,
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": null,
          "moduleIdentifier": null,
          "module": null,
          "moduleName": null,
          "type": "single entry",
          "userRequest": "./src/index1.js",
          "loc": "index1"
        }
      ],
      "usedExports": true,
      "providedExports": [],
      "optimizationBailout": [
        "ModuleConcatenation bailout: Cannot concat with ./src/b.js",
        "ModuleConcatenation bailout: Cannot concat with ./src/d.js"
      ],
      "depth": 0,
      "modules": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "name": "./src/index1.js",
          "index": 0,
          "index2": 3,
          "size": 59,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": null,
          "issuerId": null,
          "issuerName": null,
          "issuerPath": null,
          "profile": {
            "factory": 76,
            "building": 19
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": null,
              "module": null,
              "moduleName": null,
              "type": "single entry",
              "userRequest": "./src/index1.js",
              "loc": "index1"
            }
          ],
          "usedExports": true,
          "providedExports": [],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Module is an entry point"
          ],
          "depth": 0,
          "source": "import a from './a';\nimport d from './d';\n\nalert(...a(d));\n"
        },
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "name": "./src/a.js",
          "index": 1,
          "index2": 1,
          "size": 80,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "issuerId": null,
          "issuerName": "./src/index1.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 76,
                "building": 19
              }
            }
          ],
          "profile": {
            "factory": 7,
            "building": 9,
            "dependencies": 2
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "module": "./src/index1.js",
              "moduleName": "./src/index1.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./a",
              "loc": "1:0-20"
            },
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "module": "./src/index1.js",
              "moduleName": "./src/index1.js",
              "type": "harmony import specifier",
              "userRequest": "./a",
              "loc": "4:9-10"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 1,
          "source": "import b from './b';\n\nexport default (a) => import('./c').then(c => [a, b, c]);\n"
        }
      ],
      "filteredModules": 0
    },
    {
      "id": 3,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js 2f57cc9a3546f31ab3373363a50227dc",
      "name": "./src/index2.js + 1 modules",
      "index": 4,
      "index2": 5,
      "size": 84,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        1
      ],
      "issuer": null,
      "issuerId": null,
      "issuerName": null,
      "issuerPath": null,
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": null,
          "moduleIdentifier": null,
          "module": null,
          "moduleName": null,
          "type": "single entry",
          "userRequest": "./src/index2.js",
          "loc": "index2"
        }
      ],
      "usedExports": true,
      "providedExports": [],
      "optimizationBailout": [
        "ModuleConcatenation bailout: Cannot concat with ./src/d.js"
      ],
      "depth": 0,
      "modules": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
          "name": "./src/index2.js",
          "index": 4,
          "index2": 5,
          "size": 59,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": null,
          "issuerId": null,
          "issuerName": null,
          "issuerPath": null,
          "profile": {
            "factory": 65,
            "building": 20,
            "dependencies": 4
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": null,
              "module": null,
              "moduleName": null,
              "type": "single entry",
              "userRequest": "./src/index2.js",
              "loc": "index2"
            }
          ],
          "usedExports": true,
          "providedExports": [],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Module is an entry point"
          ],
          "depth": 0,
          "source": "import d from './d';\nimport e from './e';\n\nalert(...d(e));\n"
        },
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/e.js",
          "name": "./src/e.js",
          "index": 5,
          "index2": 4,
          "size": 20,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
          "issuerId": null,
          "issuerName": "./src/index2.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
              "name": "./src/index2.js",
              "profile": {
                "factory": 65,
                "building": 20,
                "dependencies": 4
              }
            }
          ],
          "profile": {
            "factory": 4,
            "building": 5
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
              "module": "./src/index2.js",
              "moduleName": "./src/index2.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./e",
              "loc": "2:0-20"
            },
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index2.js",
              "module": "./src/index2.js",
              "moduleName": "./src/index2.js",
              "type": "harmony import specifier",
              "userRequest": "./e",
              "loc": "4:11-12"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 1,
          "source": "export default 'e';\n"
        }
      ],
      "filteredModules": 0
    },
    {
      "id": 4,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/c.js",
      "name": "./src/c.js",
      "index": 6,
      "index2": 6,
      "size": 20,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        2
      ],
      "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
      "issuerId": null,
      "issuerName": "./src/a.js",
      "issuerPath": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "name": "./src/index1.js",
          "profile": {
            "factory": 76,
            "building": 19
          }
        },
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "name": "./src/a.js",
          "profile": {
            "factory": 7,
            "building": 9,
            "dependencies": 2
          }
        }
      ],
      "profile": {
        "factory": 2,
        "building": 1
      },
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": null,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "module": "./src/a.js",
          "moduleName": "./src/a.js",
          "type": "import()",
          "userRequest": "./c",
          "loc": "3:22-35"
        }
      ],
      "usedExports": true,
      "providedExports": [
        "default"
      ],
      "optimizationBailout": [
        "ModuleConcatenation bailout: Module is referenced from these modules with unsupported syntax: ./src/a.js (referenced with import())"
      ],
      "depth": 2,
      "source": "export default 'c';\n"
    }
  ],
  "filteredModules": 0,
  "children": []
} |});

let c = decodeStats({| {
  "errors": [],
  "warnings": [
    "configuration\nThe 'mode' option has not been set, webpack will fallback to 'production' for this value. Set 'mode' option to 'development' or 'production' to enable defaults for each environment.\nYou can also set it to 'none' to disable any default behavior. Learn more: https://webpack.js.org/concepts/mode/"
  ],
  "version": "4.28.4",
  "hash": "9ab378b4f6eca4e74ed6",
  "time": 130,
  "builtAt": 1547585493727,
  "publicPath": "",
  "outputPath": "/Users/eryk.napierala/Projects/webpack-stats-playground/dist",
  "assetsByChunkName": {
    "index1": "index1.js"
  },
  "assets": [
    {
      "name": "1.js",
      "size": 113,
      "chunks": [
        1
      ],
      "chunkNames": [],
      "emitted": true
    },
    {
      "name": "2.js",
      "size": 112,
      "chunks": [
        2
      ],
      "chunkNames": [],
      "emitted": true
    },
    {
      "name": "index1.js",
      "size": 2141,
      "chunks": [
        0
      ],
      "chunkNames": [
        "index1"
      ],
      "emitted": true
    }
  ],
  "filteredAssets": 0,
  "entrypoints": {
    "index1": {
      "chunks": [
        0
      ],
      "assets": [
        "index1.js"
      ],
      "children": {},
      "childAssets": {}
    }
  },
  "namedChunkGroups": {
    "index1": {
      "chunks": [
        0
      ],
      "assets": [
        "index1.js"
      ],
      "children": {},
      "childAssets": {}
    }
  },
  "chunks": [
    {
      "id": 0,
      "rendered": true,
      "initial": true,
      "entry": true,
      "size": 250,
      "names": [
        "index1"
      ],
      "files": [
        "index1.js"
      ],
      "hash": "da89655b18b608d2b2b9",
      "siblings": [],
      "parents": [],
      "children": [
        1,
        2
      ],
      "childrenByOrder": {},
      "modules": [
        {
          "id": 0,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js c1de1f3ee4ff65c59be797278155b7b7",
          "name": "./src/index1.js + 3 modules",
          "index": 0,
          "index2": 3,
          "size": 250,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            0
          ],
          "issuer": null,
          "issuerId": null,
          "issuerName": null,
          "issuerPath": null,
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": null,
              "module": null,
              "moduleName": null,
              "type": "single entry",
              "userRequest": "./src/index1.js",
              "loc": "index1"
            }
          ],
          "usedExports": true,
          "providedExports": [],
          "optimizationBailout": [],
          "depth": 0,
          "modules": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "index": 0,
              "index2": 3,
              "size": 93,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": null,
              "issuerId": null,
              "issuerName": null,
              "issuerPath": null,
              "profile": {
                "factory": 41,
                "building": 11
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": null,
                  "module": null,
                  "moduleName": null,
                  "type": "single entry",
                  "userRequest": "./src/index1.js",
                  "loc": "index1"
                }
              ],
              "usedExports": true,
              "providedExports": [],
              "optimizationBailout": [
                "ModuleConcatenation bailout: Module is an entry point"
              ],
              "depth": 0,
              "source": "import a from './a';\nimport d from './d';\n\nimport('./e').then(e => {\n  alert(...a(d, e));\n});"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "name": "./src/a.js",
              "index": 1,
              "index2": 1,
              "size": 86,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "issuerId": null,
              "issuerName": "./src/index1.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "name": "./src/index1.js",
                  "profile": {
                    "factory": 41,
                    "building": 11
                  }
                }
              ],
              "profile": {
                "factory": 3,
                "building": 5,
                "dependencies": 2
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "module": "./src/index1.js",
                  "moduleName": "./src/index1.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./a",
                  "loc": "1:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "module": "./src/index1.js",
                  "moduleName": "./src/index1.js",
                  "type": "harmony import specifier",
                  "userRequest": "./a",
                  "loc": "5:11-12"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 1,
              "source": "import b from './b';\n\nexport default (a, e) => import('./c').then(c => [a, b, c, e]);\n"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "name": "./src/d.js",
              "index": 3,
              "index2": 2,
              "size": 51,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "issuerId": null,
              "issuerName": "./src/index1.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "name": "./src/index1.js",
                  "profile": {
                    "factory": 41,
                    "building": 11
                  }
                }
              ],
              "profile": {
                "factory": 3,
                "building": 5,
                "dependencies": 2
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "module": "./src/index1.js",
                  "moduleName": "./src/index1.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./d",
                  "loc": "2:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "module": "./src/index1.js",
                  "moduleName": "./src/index1.js",
                  "type": "harmony import specifier",
                  "userRequest": "./d",
                  "loc": "5:13-14"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 1,
              "source": "import b from './b';\n\nexport default (e) => [e, b];"
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/b.js",
              "name": "./src/b.js",
              "index": 2,
              "index2": 0,
              "size": 20,
              "cacheable": true,
              "built": true,
              "optional": false,
              "prefetched": false,
              "chunks": [],
              "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "issuerId": null,
              "issuerName": "./src/a.js",
              "issuerPath": [
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
                  "name": "./src/index1.js",
                  "profile": {
                    "factory": 41,
                    "building": 11
                  }
                },
                {
                  "id": null,
                  "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "name": "./src/a.js",
                  "profile": {
                    "factory": 3,
                    "building": 5,
                    "dependencies": 2
                  }
                }
              ],
              "profile": {
                "factory": 3,
                "building": 1
              },
              "failed": false,
              "errors": 0,
              "warnings": 0,
              "assets": [],
              "reasons": [
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "module": "./src/a.js",
                  "moduleName": "./src/a.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./b",
                  "loc": "1:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
                  "module": "./src/d.js",
                  "moduleName": "./src/d.js",
                  "type": "harmony side effect evaluation",
                  "userRequest": "./b",
                  "loc": "1:0-20"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
                  "module": "./src/d.js",
                  "moduleName": "./src/d.js",
                  "type": "harmony import specifier",
                  "userRequest": "./b",
                  "loc": "3:26-27"
                },
                {
                  "moduleId": null,
                  "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
                  "module": "./src/a.js",
                  "moduleName": "./src/a.js",
                  "type": "harmony import specifier",
                  "userRequest": "./b",
                  "loc": "3:53-54"
                }
              ],
              "usedExports": [
                "default"
              ],
              "providedExports": [
                "default"
              ],
              "optimizationBailout": [],
              "depth": 2,
              "source": "export default 'b';\n"
            }
          ],
          "filteredModules": 0
        }
      ],
      "filteredModules": 0,
      "origins": [
        {
          "module": "",
          "moduleIdentifier": "",
          "moduleName": "",
          "loc": "index1",
          "request": "./src/index1.js",
          "reasons": []
        }
      ]
    },
    {
      "id": 1,
      "rendered": true,
      "initial": false,
      "entry": false,
      "size": 20,
      "names": [],
      "files": [
        "1.js"
      ],
      "hash": "e153e86d07d2b1b9d6ab",
      "siblings": [],
      "parents": [
        0
      ],
      "children": [],
      "childrenByOrder": {},
      "modules": [
        {
          "id": 2,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/c.js",
          "name": "./src/c.js",
          "index": 5,
          "index2": 5,
          "size": 20,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            1
          ],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "issuerId": null,
          "issuerName": "./src/a.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 41,
                "building": 11
              }
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "name": "./src/a.js",
              "profile": {
                "factory": 3,
                "building": 5,
                "dependencies": 2
              }
            }
          ],
          "profile": {
            "factory": 3,
            "building": 1
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "module": "./src/a.js",
              "moduleName": "./src/a.js",
              "type": "import()",
              "userRequest": "./c",
              "loc": "3:25-38"
            }
          ],
          "usedExports": true,
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Module is referenced from these modules with unsupported syntax: ./src/a.js (referenced with import())"
          ],
          "depth": 2,
          "source": "export default 'c';\n"
        }
      ],
      "filteredModules": 0,
      "origins": [
        {
          "moduleId": null,
          "module": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "moduleName": "./src/a.js",
          "loc": "3:25-38",
          "request": "./c",
          "reasons": []
        }
      ]
    },
    {
      "id": 2,
      "rendered": true,
      "initial": false,
      "entry": false,
      "size": 20,
      "names": [],
      "files": [
        "2.js"
      ],
      "hash": "a8c794c46440a0257f23",
      "siblings": [],
      "parents": [
        0
      ],
      "children": [],
      "childrenByOrder": {},
      "modules": [
        {
          "id": 1,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/e.js",
          "name": "./src/e.js",
          "index": 4,
          "index2": 4,
          "size": 20,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [
            2
          ],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "issuerId": null,
          "issuerName": "./src/index1.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 41,
                "building": 11
              }
            }
          ],
          "profile": {
            "factory": 3,
            "building": 5,
            "dependencies": 2
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "module": "./src/index1.js",
              "moduleName": "./src/index1.js",
              "type": "import()",
              "userRequest": "./e",
              "loc": "4:0-13"
            }
          ],
          "usedExports": true,
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Module is referenced from these modules with unsupported syntax: ./src/index1.js (referenced with import())"
          ],
          "depth": 1,
          "source": "export default 'e';\n"
        }
      ],
      "filteredModules": 0,
      "origins": [
        {
          "moduleId": null,
          "module": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "moduleName": "./src/index1.js",
          "loc": "4:0-13",
          "request": "./e",
          "reasons": []
        }
      ]
    }
  ],
  "modules": [
    {
      "id": 0,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js c1de1f3ee4ff65c59be797278155b7b7",
      "name": "./src/index1.js + 3 modules",
      "index": 0,
      "index2": 3,
      "size": 250,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        0
      ],
      "issuer": null,
      "issuerId": null,
      "issuerName": null,
      "issuerPath": null,
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": null,
          "moduleIdentifier": null,
          "module": null,
          "moduleName": null,
          "type": "single entry",
          "userRequest": "./src/index1.js",
          "loc": "index1"
        }
      ],
      "usedExports": true,
      "providedExports": [],
      "optimizationBailout": [],
      "depth": 0,
      "modules": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "name": "./src/index1.js",
          "index": 0,
          "index2": 3,
          "size": 93,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": null,
          "issuerId": null,
          "issuerName": null,
          "issuerPath": null,
          "profile": {
            "factory": 41,
            "building": 11
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": null,
              "module": null,
              "moduleName": null,
              "type": "single entry",
              "userRequest": "./src/index1.js",
              "loc": "index1"
            }
          ],
          "usedExports": true,
          "providedExports": [],
          "optimizationBailout": [
            "ModuleConcatenation bailout: Module is an entry point"
          ],
          "depth": 0,
          "source": "import a from './a';\nimport d from './d';\n\nimport('./e').then(e => {\n  alert(...a(d, e));\n});"
        },
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "name": "./src/a.js",
          "index": 1,
          "index2": 1,
          "size": 86,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "issuerId": null,
          "issuerName": "./src/index1.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 41,
                "building": 11
              }
            }
          ],
          "profile": {
            "factory": 3,
            "building": 5,
            "dependencies": 2
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "module": "./src/index1.js",
              "moduleName": "./src/index1.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./a",
              "loc": "1:0-20"
            },
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "module": "./src/index1.js",
              "moduleName": "./src/index1.js",
              "type": "harmony import specifier",
              "userRequest": "./a",
              "loc": "5:11-12"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 1,
          "source": "import b from './b';\n\nexport default (a, e) => import('./c').then(c => [a, b, c, e]);\n"
        },
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
          "name": "./src/d.js",
          "index": 3,
          "index2": 2,
          "size": 51,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "issuerId": null,
          "issuerName": "./src/index1.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 41,
                "building": 11
              }
            }
          ],
          "profile": {
            "factory": 3,
            "building": 5,
            "dependencies": 2
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "module": "./src/index1.js",
              "moduleName": "./src/index1.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./d",
              "loc": "2:0-20"
            },
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "module": "./src/index1.js",
              "moduleName": "./src/index1.js",
              "type": "harmony import specifier",
              "userRequest": "./d",
              "loc": "5:13-14"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 1,
          "source": "import b from './b';\n\nexport default (e) => [e, b];"
        },
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/b.js",
          "name": "./src/b.js",
          "index": 2,
          "index2": 0,
          "size": 20,
          "cacheable": true,
          "built": true,
          "optional": false,
          "prefetched": false,
          "chunks": [],
          "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "issuerId": null,
          "issuerName": "./src/a.js",
          "issuerPath": [
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
              "name": "./src/index1.js",
              "profile": {
                "factory": 41,
                "building": 11
              }
            },
            {
              "id": null,
              "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "name": "./src/a.js",
              "profile": {
                "factory": 3,
                "building": 5,
                "dependencies": 2
              }
            }
          ],
          "profile": {
            "factory": 3,
            "building": 1
          },
          "failed": false,
          "errors": 0,
          "warnings": 0,
          "assets": [],
          "reasons": [
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "module": "./src/a.js",
              "moduleName": "./src/a.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./b",
              "loc": "1:0-20"
            },
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "module": "./src/d.js",
              "moduleName": "./src/d.js",
              "type": "harmony side effect evaluation",
              "userRequest": "./b",
              "loc": "1:0-20"
            },
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/d.js",
              "module": "./src/d.js",
              "moduleName": "./src/d.js",
              "type": "harmony import specifier",
              "userRequest": "./b",
              "loc": "3:26-27"
            },
            {
              "moduleId": null,
              "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
              "module": "./src/a.js",
              "moduleName": "./src/a.js",
              "type": "harmony import specifier",
              "userRequest": "./b",
              "loc": "3:53-54"
            }
          ],
          "usedExports": [
            "default"
          ],
          "providedExports": [
            "default"
          ],
          "optimizationBailout": [],
          "depth": 2,
          "source": "export default 'b';\n"
        }
      ],
      "filteredModules": 0
    },
    {
      "id": 1,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/e.js",
      "name": "./src/e.js",
      "index": 4,
      "index2": 4,
      "size": 20,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        2
      ],
      "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
      "issuerId": null,
      "issuerName": "./src/index1.js",
      "issuerPath": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "name": "./src/index1.js",
          "profile": {
            "factory": 41,
            "building": 11
          }
        }
      ],
      "profile": {
        "factory": 3,
        "building": 5,
        "dependencies": 2
      },
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": null,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "module": "./src/index1.js",
          "moduleName": "./src/index1.js",
          "type": "import()",
          "userRequest": "./e",
          "loc": "4:0-13"
        }
      ],
      "usedExports": true,
      "providedExports": [
        "default"
      ],
      "optimizationBailout": [
        "ModuleConcatenation bailout: Module is referenced from these modules with unsupported syntax: ./src/index1.js (referenced with import())"
      ],
      "depth": 1,
      "source": "export default 'e';\n"
    },
    {
      "id": 2,
      "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/c.js",
      "name": "./src/c.js",
      "index": 5,
      "index2": 5,
      "size": 20,
      "cacheable": true,
      "built": true,
      "optional": false,
      "prefetched": false,
      "chunks": [
        1
      ],
      "issuer": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
      "issuerId": null,
      "issuerName": "./src/a.js",
      "issuerPath": [
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/index1.js",
          "name": "./src/index1.js",
          "profile": {
            "factory": 41,
            "building": 11
          }
        },
        {
          "id": null,
          "identifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "name": "./src/a.js",
          "profile": {
            "factory": 3,
            "building": 5,
            "dependencies": 2
          }
        }
      ],
      "profile": {
        "factory": 3,
        "building": 1
      },
      "failed": false,
      "errors": 0,
      "warnings": 0,
      "assets": [],
      "reasons": [
        {
          "moduleId": null,
          "moduleIdentifier": "/Users/eryk.napierala/Projects/webpack-stats-playground/src/a.js",
          "module": "./src/a.js",
          "moduleName": "./src/a.js",
          "type": "import()",
          "userRequest": "./c",
          "loc": "3:25-38"
        }
      ],
      "usedExports": true,
      "providedExports": [
        "default"
      ],
      "optimizationBailout": [
        "ModuleConcatenation bailout: Module is referenced from these modules with unsupported syntax: ./src/a.js (referenced with import())"
      ],
      "depth": 2,
      "source": "export default 'c';\n"
    }
  ],
  "filteredModules": 0,
  "children": []
} |});

let ab = Compare.compare(a, b);
let bc = Compare.compare(b, c);

let logStats = (title, stats) => {
  Js.log(title);
  stats |> Stats.encode |> Js.log;
};

let logComp = (title, comp) => {
  Js.log(title);
  comp |> Compare.encode |> Js.log;
}

logStats("a", a);
logStats("b", b);
logStats("c", c);

logComp("a VS b", ab);
logComp("b VS c", bc);
