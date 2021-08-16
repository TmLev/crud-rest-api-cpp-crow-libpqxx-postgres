# Base Focal image
FROM ubuntu:20.04

# Install dependencies & tools
COPY docker/install-deps.sh /
RUN sh install-deps.sh

# Set system language
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

# Export compilers
ENV CC "/usr/bin/clang-12"
ENV CXX "/usr/bin/clang++-12"

# Set working directory
WORKDIR /rest-api
