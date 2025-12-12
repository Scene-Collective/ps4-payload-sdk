#!/bin/bash

# DEPRECIATED: Left for example on how you *could* install it

# Install prerequisites if root
if [ "$EUID" -ne 0 ]; then
  echo "Not root, skipping update and install"
  exit
else
  apt-get update
  apt-get install -y --no-install-recommends build-essential binutils gcc make
fi

# Delete directory if it exists and make empty directory
if [ "$PWD" != "/lib/ps4-payload-sdk" ]; then
  rm -rf /lib/ps4-payload-sdk || true
  mkdir -p /lib/ps4-payload-sdk
fi

# Build SDK
cd libPS4 || (echo "Unable to enter subdirectory" && exit)
make
cd ..

# Copy compiled SDK
if [ "$PWD" != "/lib/ps4-payload-sdk" ]; then
  cp -r libPS4 /lib/ps4-payload-sdk
  cp install.sh /lib/ps4-payload-sdk/update.sh
fi

# Clear path from .bashrc if it's there
sed -i "s/^\s*export PS4SDK=.*//gm" /etc/profile

# Add to paths
echo "export PS4SDK=/lib/ps4-payload-sdk" | tee -a /etc/profile
export PS4SDK=/lib/ps4-payload-sdk
