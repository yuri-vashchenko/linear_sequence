LABEL \
    Description="This docker image contains environment for C/C++ code building and testing with CppUTest" \
    MAINTAINER="Yuri Vashchenko <yuri.vashchenko@gmail.com>"
FROM ubuntu:latest
RUN apt update && apt install -y --no-install-recommends \
        build-essential \
        cpputest \
    && rm -rf /var/lib/apt/lists/*

