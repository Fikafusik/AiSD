#!/bin/bash 
make 
if [ -f "result.txt" ]; then
    rm result.txt 
fi
touch result.txt 
for i in $(ls Tests/Correct); do 
    echo "running test: \"Tests/Correct/$i\" "; 
    sleep 0.2s;
    echo "correct brackets test: \"$i\"" >>result.txt;
    ./lexical_analyzer <Tests/Correct/$i >>result.txt; 
done; 
for i in $(ls Tests/Incorrect); do 
    echo "running test: \"Tests/Incorrect/$i\" "; 
    sleep 0.2s;
    echo "incorrect brackets test: \"$i\"" >>result.txt;
    ./lexical_analyzer <Tests/Incorrect/$i >>result.txt; 
done; 
make clean 
