#!/bin/bash

make &&
sudo rmmod phas2.ko && echo "\t***\trmmod phas2.ko done\t***\t" &&
sudo insmod phas2.ko && echo "\t***\tinsmod phas2.ko done\t***\t" &&
gcc -o testphas2 testphas2.c && ./testphas2 && 
tail -n 10 /var/log/syslog
