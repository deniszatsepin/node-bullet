#!/bin/sh

cd libbullet
CFLAGS="-fPIC" CXXFLAGS="-fPIC" \
	./configure --disable-demos --disable-shared
make

