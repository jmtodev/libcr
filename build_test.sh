#!/bin/bash
if [[ $1 == "aarch64" ]]; then
  echo "BUILD ARM-64"
  export CROSS_COMPILER=aarch64-linux-gnu-
  export CC=${CROSS_COMPILER}gcc
  export AR=${CROSS_COMPILER}ar
  export CFLAGS=""
  export LDFLAGS=""
  export ARCH="aarch64"
elif [[ $1 == "armv7" ]]; then
  echo "BUILD ARMV7"
  export CROSS_COMPILER=arm-linux-gnueabihf-
  export CC=${CROSS_COMPILER}gcc
  export AR=${CROSS_COMPILER}ar
  export CFLAGS=""
  export LDFLAGS=""
  export ARCH="armv7"
else
  echo "BUILD x86-64"
  export CC=gcc
  export AR=ar
  export CFLAGS=""
  export LDFLAGS="-lz"
  export ARCH="amd64"
fi

mkdir -p bin
echo "BUILD EXAMPLE"
${CC} -O2 $CFLAGS \
  example/testlibcr.c \
  lib/libcr-$ARCH.a \
  -Iinclude \
  -o bin/testlibcr-$ARCH \
  $LDFLAGS -lpthread

echo "FINISH...";

