#!/bin/bash

# Function to install prerequisites for Debian-based systems (including Ubuntu)
install_debian() {
  apt-get update
  apt-get -y install binutils gcc make
}

# Function to install prerequisites for Fedora
install_fedora() {
  dnf install -y binutils binutils-gold gcc make
}

# Function to install prerequisites for Arch
install_arch() {
  pacman -Sy --noconfirm binutils gcc make
}

# Detect the distribution
if [ "$EUID" -ne 0 ]; then
  echo "Not root, skipping update and install"
  exit
fi

# Check for various distributions
if [ -f /etc/os-release ]; then
  . /etc/os-release
  case "$ID" in
    ubuntu|debian)
      install_debian
      ;;
    fedora)
      install_fedora
      ;;
    arch)
      install_arch
      ;;
    *)
      echo "Unsupported distribution: $ID"
      exit 1
      ;;
  esac
else
  echo "Unsupported distribution"
  exit 1
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
