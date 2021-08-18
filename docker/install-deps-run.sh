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

# Make Postgres repos visible for `apt`.
wget -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | apt-key add -
echo "deb http://apt.postgresql.org/pub/repos/apt/ `lsb_release -cs`-pgdg main" | tee /etc/apt/sources.list.d/pgdg.list

# Update system once again.
apt-get update

# Don't ask me anything.
export DEBIAN_FRONTEND=noninteractive

# `libpqxx` dependencies.
apt-get install -y \
  postgresql-client-13
