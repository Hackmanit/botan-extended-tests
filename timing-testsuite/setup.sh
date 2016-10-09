#!/bin/sh

if [ ! -d botan ]
then
    git clone https://github.com/randombit/botan.git
fi

if [ ! -d mona-timing-report ]
then
    git clone https://github.com/seecurity/mona-timing-report.git
fi

cd botan
git checkout .
git pull
patch src/lib/tls/tls_cbc.h ../misc/tls_cbc.patch
./configure.py
make -j4

cd ..
cd mona-timing-report
ant