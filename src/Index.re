let data = {| {
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
} |}
let decoded = data |> Json.parseOrRaise |> Stats.decode

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
Js.log(("chunks", decoded.chunks));
