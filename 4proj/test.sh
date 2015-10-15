#!/bin/bash
# Ian Jacoway
# irjacoway
# CS3013 A15 Proj4

echo "clean" && make clean &&
echo "make" && make &&
echo "usage" && ./proj4 2 &&
echo "test multithreading with up to 15 running parallel"
for t_limit in {1 2 3 4 5 6 7 8 9 10 11 12 13 14 15}
do
ls -1d * | /home/cali/Desktop/cs3013/4proj/proj4 threads $t_limit
done
echo "current directory contains" && ls
