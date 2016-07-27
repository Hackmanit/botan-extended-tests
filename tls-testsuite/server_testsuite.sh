#!/bin/sh

if [ -d tls-testsuite ] 
then
    cd tls-testsuite
fi

botan/botan tls_server TLS-Attacker/resources/rsa1024cert.pem TLS-Attacker/resources/rsa1024key.pem --port=4433 > output/server_output.log 2>&1 &
botan_pid=$!

java -jar TLS-Attacker/Runnable/target/TLS-Attacker-1.1.jar -loglevel INFO testsuite_server -folder TLS-Attacker/resources/testsuite -tls_timeout 1000
rc=$?

if [ $rc -eq 0 ]; then
    echo Tests finished without failures
else
    echo '\n\nTests failed. Server log output:\n\n'
    cat output/server_output.log
fi

kill $botan_pid
exit $rc