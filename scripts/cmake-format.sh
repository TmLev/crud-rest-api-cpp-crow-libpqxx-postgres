#! /usr/bin/env bash

cmake-format \
  --in-place \
  CMakeLists.txt cmake/* dependencies/CMakeLists.txt src/CMakeLists.txt
