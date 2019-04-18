#!/usr/bin/env bash

set -e

pushd "$(dirname "$0")" > /dev/null

cp .clang-format.doxygen .clang-format

clang-format -i src/* test/*

rm .clang-format

doxygen Doxyfile

./format.sh

popd > /dev/null
