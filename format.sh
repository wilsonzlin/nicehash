#!/usr/bin/env bash

set -e

pushd "$(dirname "$0")" > /dev/null

clang-format -i src/* test/*

popd > /dev/null
