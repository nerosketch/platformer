#!/bin/bash -

PATH=/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/sbin

git submodule init
git submodule update
cmake .
make -j3
./platformer
