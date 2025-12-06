#!/bin/bash

# DEPRECIATED: Left for example on how you *could* install it

# Install prerequisites if root
if [ "$EUID" -ne 0 ]; then
  echo "Not root, skipping update and install"
  exit
else
  DISTRO=$( lsb_release -i | cut -f 2- | tr '[:upper:]' '[:lower:]' )
  if [[ $DISTRO == "ubuntu" ]] then
    apt-get update
    apt-get install -y --no-install-recommends binutils gcc make
  elif [[ $DISTRO == "opensuse" ]] then
    zypper install -y binutils gcc make
  elif [[ $DISTRO == "fedora" ]] then
    dnf install -y binutils binutils-gold gcc make
  else
    echo "OS not implemented yet, please manually install the required libraries and then continue (binutils, gcc and make)."
    read -p "Have you installed the required libraries? " yn
    if [ $yn != [yY] || $yn != [yY][eE][sS] ]] then
      exit
    fi
  fi
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
