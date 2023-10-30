#!/bin/bash

scripts_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ws_path="$(dirname "$scripts_path")"

rm -rf $ws_path/build
rm -rf $ws_path/devel
rm -rf $ws_path/install
rm -rf $ws_path/.cache
rm -rf $ws_path/src/CMakeLists.txt