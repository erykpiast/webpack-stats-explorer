#!/usr/bin/env bash

find src -name "*.re" | while read FILE; do
    echo "Upgrading $FILE";
    ./node_modules/upgrade-reason-react/lib/bs/bytecode/migrate.byte "$FILE";
done;
