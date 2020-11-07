#!/usr/bin/env zsh

set -e;

OLD_PWD=$(pwd);
N="$1";
VERSIONS=("a" "b" "c" "d" "e" "f" "g" "h" "i" "j");

echo "version,iteration,build_time" > times.log

for VERSION in ${VERSIONS[*]}; do
    DIR="$OLD_PWD/$VERSION";

    echo "Measuring version \"$VERSION\" $N times...";

    if [[ -d "$DIR" ]]; then
        cd "$DIR";
            
        [[ -d "./node_modules" ]] || npm ci;

        for I in {1..$N}; do
            echo "Iteration $I...";

            npm run build;

            BUILD_TIME=$(cat "../$VERSION.json" | jq ".time");
            echo "$VERSION,$I,$BUILD_TIME" >> "../times.csv";
        done;
    fi;
done;

cd "$OLD_PWD";

set +e;
