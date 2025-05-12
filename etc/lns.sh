#!/bin/sh

find lib inc src -type f -name '*[.h|.cpp]' -exec cat {} \; | wc -l
find lib inc src -type f -name '*[.h|.cpp]' -exec wc -l {} \;
