#!/bin/sh

if [ ! -d botan ]
then
    git clone https://github.com/randombit/botan.git
fi

if [ ! -d TLS-Attacker ]
then
    git clone https://github.com/RUB-NDS/TLS-Attacker.git
fi

mkdir output

cd botan
git checkout .
git pull
patch src/cli/tls_server.cpp ../misc/tls_server.patch

export ASAN_OPTIONS=check_initialization_order=true
./configure.py --with-sanitizers --disable-shared --with-debug-info --with-bzip2 --with-lzma --with-sqlite --with-zlib --cc="$CC" --cc-bin="$CXX"
make -j4

cd ..
cd TLS-Attacker
git checkout .
git pull
./mvnw clean package -DskipTests=true
