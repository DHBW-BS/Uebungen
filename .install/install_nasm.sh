#!/usr/bin/bash

VERSION="2.16.03"

wget https://www.nasm.us/pub/nasm/releasebuilds/${VERSION}/nasm-${VERSION}.tar.gz
tar xvfz nasm-${VERSION}.tar.gz
cd nasm-${VERSION}
./configure
make

cp nasm ${HOME}/.local/bin

exit 0
