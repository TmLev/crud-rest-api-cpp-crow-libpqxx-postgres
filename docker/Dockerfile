# ------------------------------------------------------------------------------
# Stage 1. Build.

# Base Focal image.
FROM ubuntu:20.04 as BUILD

# Install build dependencies & tools.
COPY docker/install-deps-build.sh /
RUN sh install-deps-build.sh

# Set system language.
ENV LANG C.UTF-8
ENV LC_ALL C.UTF-8

# Export compilers.
ENV CC "/usr/bin/clang-12"
ENV CXX "/usr/bin/clang++-12"

# Set working directory.
WORKDIR /rest-api

# Copy code.
COPY cmake cmake
COPY dependencies dependencies
COPY src src
COPY CMakeLists.txt ./

# Build CMake project and target.
RUN mkdir cmake-build && \
    cd cmake-build && \
    cmake .. && \
    make rest-api

# ------------------------------------------------------------------------------
# Stage 2. Run.

# Base Focal image.
FROM ubuntu:20.04

# Install runtime dependencies.
COPY docker/install-deps-run.sh /
RUN sh install-deps-run.sh

# Set working directory.
WORKDIR /rest-api

# Copy binary.
COPY --from=BUILD /rest-api/cmake-build/src/rest-api ./

# Run server.
CMD ["./rest-api"]
