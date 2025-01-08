#!/bin/bash
root_path=$(dirname "$(readlink -f "$0")")
project_name=$(basename $root_path)
build_path="$root_path/build/linux"
if [ ! -d "$build_path" ]; then
    mkdir -p "$build_path"
fi
cd $build_path
cmake ../..
make
cd ../..
mv "$build_path/$project_name" "$root_path/binary"
