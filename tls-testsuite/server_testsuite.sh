#!/bin/sh

if [ -d tls-testsuite ] 
then
    cd tls-testsuite
fi

botan/botan tls_server TLS-Attacker/resources/rsa1024cert.pem TLS-Attacker/resources/rsa1024key.pem --port=4433 > output/server_output.log 2>&1 &
botan_pid=$!

java -jar TLS-Attacker/Runnable/target/TLS-Attacker-1.1.jar -loglevel INFO testsuite_server -folder TLS-Attacker/resources/testsuite -tls_timeout 1000

kill $botan_pid