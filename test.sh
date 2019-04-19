#!/usr/bin/env bash

pushd "$(dirname "$0")/test" > /dev/null

for t in *.c; do
  if [ "$t" == _* ]; then
    continue
  fi

  echo "Running test $t..."
  tmp="$(mktemp)"
  gcc --std=c11 -Wall -Wextra -Werror -Wno-type-limits -O0 -g -I../src -o "$tmp" "$t"
  if [ $? -ne 0 ]; then
    echo "Compiling $t failed"
    exit 2
  fi
  "$tmp"
  result=$?
  rm "$tmp"
  if [ $result -ne 0 ]; then
    echo "Test $t failed"
    exit 1
  fi
done

echo "All tests passed successfully"

popd > /dev/null
