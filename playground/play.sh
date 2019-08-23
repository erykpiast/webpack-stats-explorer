#!/usr/bin/env bash

set -e;

OLD_PWD=$(pwd);

EXAMPLE=$1;

cd "playground/$EXAMPLE/v1";
[[ -d "./node_modules" ]] || npm ci;
npm run build;

cd $OLD_PWD;

cd "playground/$EXAMPLE/v2";
[[ -d "./node_modules" ]] || npm ci;
npm run build;

cd $OLD_PWD;

set +e;
