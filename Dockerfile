FROM ubuntu:latest

RUN apt update && apt install -y --no-install-recommends \
        build-essential \
        cpputest \
	cmake \
    && rm -rf /var/lib/apt/lists/*

ADD . /code
WORKDIR /code
RUN ./build.sh
