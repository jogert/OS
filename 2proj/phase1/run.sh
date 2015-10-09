#!/bin/bash

make &&
sudo rmmod phas1.ko && echo "\t***\trmmod phas1.ko done\t***\t" &&
sudo insmod phas1.ko && echo "\t***\tinsmod phas1.ko done\t***\t" &&
gcc -o testphas1 testphas1.c && ./testphas1 && 
tail -n 10 /var/log/syslog
