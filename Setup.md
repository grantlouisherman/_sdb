# Vcpkg Build Environment Setup on Ubuntu

This guide explains how to set up a working build environment for **vcpkg** on Ubuntu, fix common compiler/configure errors, and successfully build packages like `libedit`.  

It captures all steps taken to resolve issues such as missing compilers, build tools, terminal libraries, and pkg-config.

---

## Overview

While building packages with vcpkg, several configuration errors can occur due to missing tools or libraries. Common issues include:

- `CMAKE_MAKE_PROGRAM is not set`  
- `CMAKE_CXX_COMPILER not set, after EnableLanguage`  
- `configure: error: libncurses, libcurses, libtermcap or libtinfo is required!`  
- `Could not find a package configuration file provided by "PKGConfig"`  

This guide explains how to resolve these errors.

---

## 1. Install Core Build Dependencies

Make sure all essential build tools and libraries are installed:

```bash
sudo apt update
sudo apt install -y \
  build-essential \
  cmake \
  ninja-build \
  autoconf \
  automake \
  libtool \
  pkg-config \
  libncurses5-dev \
  libtinfo-dev \
  curl \
  git

export CC=/usr/bin/gcc
export CXX=/usr/bin/g++

which gcc
which g++

rm -rf /dev_env/vcpkg/buildtrees/*

/dev_env/vcpkg/bootstrap-vcpkg.sh
/dev_env/vcpkg/vcpkg install

## Docker File
FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    autoconf \
    automake \
    libtool \
    pkg-config \
    libncurses5-dev \
    libtinfo-dev \
    curl \
    git

WORKDIR /dev_env
COPY . .

RUN ./vcpkg/bootstrap-vcpkg.sh

## Docker Image Locally

docker pull ubuntu
docker run -it --name linux-workstation ubuntu


docker run -it my-linux-workstation