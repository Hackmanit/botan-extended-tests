#!/bin/sh

if [ -d tls-testsuite ] 
then
    cd tls-testsuite
fi

botan/botan tls_server rsa2048cert.pem rsa2048key.pem --port=4434 --policy=botan/tls-policy/BSI_TR-02102-2.txt > output/server_output2.log 2>&1 &
botan_pid=$!

java -jar TLS-Attacker/Runnable/target/TLS-Attacker-1.1.jar -loglevel ERROR testtls_server -policy botan/tls-policy/BSI_TR-02102-2.txt -connect localhost:4434 -tls_timeout 1000
rc=$?

if [ $rc -eq 0 ]; then
    echo Policy tests finished without failures
else
    echo '\n\nPolicy tests failed. Server log output:\n\n'
    cat output/server_output2.log
fi

kill $botan_pid
exit $rc