#!/bin/sh

cd timing-tests
./main

cd ..
cd mona-timing-report

for dir in ../timing-tests/results/*; 
do
    echo "Working in directory: " $dir
    for file in $dir/*;
    do
        echo "Creating report for: " $file
        java -jar ReportingTool.jar --inputFile=$file --name=$file --lowerBound=0.4 --upperBound=0.5
    done
done