#!/bin/sh

cd timing-tests
./main

cd ..
cd mona-timing-report

for file in ../timing-tests/results/bleichenbacher/*; 
do
    echo "Creating report for: " $file
    java -jar ReportingTool.jar --inputFile=$file --name=$file --lowerBound=0.4 --upperBound=0.5
done