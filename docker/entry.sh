#!/bin/bash -l

args=$@

cd /src/$BUILDER_START_PATH

eval $args
