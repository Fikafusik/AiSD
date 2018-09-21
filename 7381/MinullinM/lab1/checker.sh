#!/bin/bash 
make 
if [ -f "result.txt" ]; then
    rm result.txt 
fi
touch result.txt 
for i in $(ls tests/correct); do 
    echo "running test: \"tests/correct/$i\" "; 
    sleep 0.13s;
    echo "correct test: \"$i\"" >>result.txt;
    ./binary_rocker <tests/correct/$i >>result.txt; 
done; 
for i in $(ls tests/incorrect); do 
    echo "running test: \"tests/incorrect/$i\" "; 
    sleep 0.13s;
    echo "incorrect test: \"$i\"" >>result.txt;
    ./binary_rocker <tests/incorrect/$i >>result.txt; 
done; 
make clean 
