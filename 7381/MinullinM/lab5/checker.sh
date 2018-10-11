#!/bin/bash 
make 
if [ -f "result.txt" ]; then
    rm result.txt 
fi
touch result.txt 
for i in $(ls tests/default); do 
    echo "running test: \"tests/default/$i\" "; 
    sleep 0.05s;
    echo "default test: \"$i\"" >>result.txt;
    ./avl_tree <tests/default/$i >>result.txt; 
done; 
for i in $(ls tests/random); do 
    echo "running test: \"tests/random$i\" "; 
    sleep 0.05s;
    echo "random test: \"$i\"" >>result.txt;
    ./avl_tree <tests/random/$i >>result.txt; 
done; 
make clean 
