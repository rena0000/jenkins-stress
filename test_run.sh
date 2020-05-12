#!/bin/bash
make clean
make all

for x in {1..12}
do
    echo "Test $x"
    cd ./t$x
    ../mstdriver < test.in.txt > my.out
    diff test.out.txt my.out
    cd ../
    echo ".......cat ..........."
done

