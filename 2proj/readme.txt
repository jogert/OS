/* Ian J & Derek M */

**Disclaimer**
Both phases work completely but not one after the other
regardless of rmmod-ing the .ko file

Solution:
Compile one mod then shutdow VBox and compile the other

PHASE1-SYSLOG.txt was from Ian's VBox Machine
PHASE2-SYSLOG.txt was from Derek's VBox Machine
**************



Type the following to compile:

(In phase1 directory):

make &&
sudo insmod phas1.ko && echo "\t***\tinsmod phas1.ko done\t***\t" &&
gcc -o testphas1 testphas1.c && ./testphas1 && 
tail -n 10 /var/log/syslog

(In phase2 directory):

make &&
sudo rmmod phas2.ko && echo "\t***\trmmod phas2.ko done\t***\t" &&
sudo insmod phas2.ko && echo "\t***\tinsmod phas2.ko done\t***\t" &&
gcc -o testphas2 testphas2.c && ./testphas2 && 
tail -n 10 /var/log/syslog

