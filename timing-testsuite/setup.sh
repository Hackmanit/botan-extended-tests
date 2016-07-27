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
    ./configure.py
    make -j4
fi

cd ..
cd mona-timing-report
ant