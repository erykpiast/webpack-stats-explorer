#!/usr/bin/env bash

set -e;

OLD_PWD=$(pwd);
EXAMPLE=$1;
VERSIONS=("a" "b" "c" "d" "e" "f");

for VERSION in ${VERSIONS[*]}; do
    DIR="$OLD_PWD/playground/$EXAMPLE/$VERSION";

    if [[ -d "$DIR" ]]; then
        cd "$DIR";
        [[ -d "./node_modules" ]] || npm ci;
        npm run build;
    fi;
done;

cd "$OLD_PWD";

set +e;
