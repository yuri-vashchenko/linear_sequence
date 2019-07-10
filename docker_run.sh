#!/bin/bash

set -e
if [ x"$DEBUG" = "xy" ]
then
    set -x
fi

script_name=$(basename $0)

ARGS=$@

PWD_REL=
# export HOME into container to allow ccache make caches
DOCKER_ARGS="${DOCKER_ARGS} -e HOME -v ${HOME}:${HOME}"

DOCKER_ARGS="${DOCKER_ARGS} --rm \
    -it \
    -e BUILDER_START_PATH=${PWD_REL}"

case "$1" in
    --shell)
        ARGS="/bin/bash"
        ;;
    *)
        ;;
esac

IMAGE=linear_sequence_simple

DOCKER_ARGS="${DOCKER_ARGS} -v $(pwd):/src"

docker run $DOCKER_ARGS $IMAGE:latest $ARGS

