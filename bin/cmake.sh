#!/usr/bin/env bash
set -x
set -e

(
    cd $(dirname "$0")/..
    cmake-converter -s GridFight/GridFight.sln
    cmake GridFight
)
