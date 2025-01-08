#!/bin/bash
root_path=$(dirname "$(readlink -f "$0")")
build_path="$root_path/build/linux"
binary_path="$root_path/binary"
if [ -d "$build_path" ]; then
    rm -rf "$build_path"
fi
if [ -e "$binary_path" ]; then
    rm -rf "$binary_path"
fi
