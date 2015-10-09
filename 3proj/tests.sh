#!/bin/bash
# Ian J

echo "clean" && make clean &&
echo "make" && make &&
echo "usage" && ./maze &&
echo "test algs with rats up to 5 rats"
for rat in {1 2 3 4 5}
do
./maze $rat i && ./maze $rat d && ./maze $rat n
done
