#! /usr/bin/env bash

# -e == exits as soon as any command in the script fails.
# -x == prints each command that is going to be executed with a little plus.
set -e -x

# Update system.
apt-get update

# Install common utils.
apt-get install -y \
  gpg \
  wget \
  software-properties-common

# Make LLVM repos visible for `apt`.
wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add -
add-apt-repository -s "deb https://apt.llvm.org/focal/ llvm-toolchain-focal-12 main"

# Make CMake repos visible for `apt`.
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg
echo "deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ focal main" | tee /etc/apt/sources.list.d/kitware.list

# Make Postgres repos visible for `apt`.
wget -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | apt-key add -
echo "deb https://apt.postgresql.org/pub/repos/apt/ `lsb_release -cs`-pgdg main" | tee /etc/apt/sources.list.d/pgdg.list

# Update system once again.
apt-get update

# Don't ask me anything.
export DEBIAN_FRONTEND=noninteractive

# Compiler.
apt-get install -y \
  clang-12

# Build tools.
apt-get install -y \
  autoconf \
  ccache \
  cmake \
  make \
  python3 \
  python3-pip

# Dev tools.
apt-get install -y \
  clang-format-12 \
  clang-tidy-12 \
  gdb \
  git \
  lldb-12 \
  vim

# More dev tools.
pip3 install \
  cmake_format[YAML]

# `crow` dependencies.
apt-get install -y \
  build-essential \
  libboost-all-dev

# `libpqxx` dependencies.
apt-get install -y \
  postgresql-13 \
  libpq-dev \
  postgresql-server-dev-all
