#!/usr/bin/env bash

set -e

pushd "$(dirname "$0")" > /dev/null

cp .clang-format.standard .clang-format

clang-format -i src/* test/*

rm .clang-format

popd > /dev/null
