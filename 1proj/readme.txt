Ian J

*** none spent more hours trying to get the times right than anthing else and they are still goofy on my local machine, I've had many many sets of eyes look into this issue as well. ***


Script started on Fri Sep  4 00:00:36 2015
[?1034hbash-3.2$ ./doit 
==> g++ -o doit doit.cpp
+++++++++++++++++STATS++++++++++++++++

User time: 0.162906000
System time: 0.18912000
Wall-Clock elapsed: 0

Process preempted involuntarily: 25
Process gave up the CPU voluntarily: 5
Major page faults: 4
Minor page faults: 7437
+++++++++++++++++++++++++++++++++++++++==> ./doit ./doit
==> mv typescript readme.txt
+++++++++++++++++STATS++++++++++++++++

User time: 0.1372000
System time: 0.1668000
Wall-Clock elapsed: 0

Process preempted involuntarily: 3
Process gave up the CPU voluntarily: 0
Major page faults: 0
Minor page faults: 198
+++++++++++++++++++++++++++++++++++++++==> ls
doit		doit.cpp	readme.txt	sh2.cpp
+++++++++++++++++STATS++++++++++++++++

User time: 0.2613000
System time: 0.2775000
Wall-Clock elapsed: 0

Process preempted involuntarily: 4
Process gave up the CPU voluntarily: 0
Major page faults: 0
Minor page faults: 440
+++++++++++++++++++++++++++++++++++++++==> mkdir fun
+++++++++++++++++STATS++++++++++++++++

User time: 0.3618000
System time: 0.4143000
Wall-Clock elapsed: 0

Process preempted involuntarily: 5
Process gave up the CPU voluntarily: 0
Major page faults: 0
Minor page faults: 637
+++++++++++++++++++++++++++++++++++++++==> cd fun
+++++++++++++++++STATS++++++++++++++++

User time: 0.7354000
System time: 0.7742000
Wall-Clock elapsed: 0

Process preempted involuntarily: 10
Process gave up the CPU voluntarily: 4
Major page faults: 0
Minor page faults: 1577
+++++++++++++++++++++++++++++++++++++++==> cd ..
+++++++++++++++++STATS++++++++++++++++

User time: 0.10739000
System time: 0.11438000
Wall-Clock elapsed: 0

Process preempted involuntarily: 16
Process gave up the CPU voluntarily: 8
Major page faults: 0
Minor page faults: 2521
+++++++++++++++++++++++++++++++++++++++==> cp doit fun
+++++++++++++++++STATS++++++++++++++++

User time: 0.11798000
System time: 0.12459000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 17
Process gave up the CPU voluntarily: 8
Major page faults: 0
Minor page faults: 2727
+++++++++++++++++++++++++++++++++++++++==> ls
doit		doit.cpp	fun		readme.txt	sh2.cpp
+++++++++++++++++STATS++++++++++++++++

User time: 0.13479000
System time: 0.13833000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 18
Process gave up the CPU voluntarily: 8
Major page faults: 0
Minor page faults: 2969
+++++++++++++++++++++++++++++++++++++++==> cd fun
+++++++++++++++++STATS++++++++++++++++

User time: 0.17164000
System time: 0.17848000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 23
Process gave up the CPU voluntarily: 12
Major page faults: 0
Minor page faults: 3909
+++++++++++++++++++++++++++++++++++++++==> ls
doit
+++++++++++++++++STATS++++++++++++++++

User time: 0.18388000
System time: 0.18979000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 24
Process gave up the CPU voluntarily: 12
Major page faults: 0
Minor page faults: 4151
+++++++++++++++++++++++++++++++++++++++==> cd ..
+++++++++++++++++STATS++++++++++++++++

User time: 0.21780000
System time: 0.22633000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 29
Process gave up the CPU voluntarily: 16
Major page faults: 0
Minor page faults: 5095
+++++++++++++++++++++++++++++++++++++++==> rm -rf fun
+++++++++++++++++STATS++++++++++++++++

User time: 0.22865000
System time: 0.24260000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 31
Process gave up the CPU voluntarily: 16
Major page faults: 0
Minor page faults: 5298
+++++++++++++++++++++++++++++++++++++++==> ls
doit		doit.cpp	readme.txt	sh2.cpp
+++++++++++++++++STATS++++++++++++++++

User time: 0.24558000
System time: 0.25674000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 32
Process gave up the CPU voluntarily: 16
Major page faults: 0
Minor page faults: 5540
+++++++++++++++++++++++++++++++++++++++==> echo "shells in shells in shells"
"shells in shells in shells"
+++++++++++++++++STATS++++++++++++++++

User time: 0.25574000
System time: 0.26500000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 33
Process gave up the CPU voluntarily: 16
Major page faults: 0
Minor page faults: 5736
+++++++++++++++++++++++++++++++++++++++==> exit
+++++++++++++++++STATS++++++++++++++++

User time: 0.190416000
System time: 0.50274000
Wall-Clock elapsed: 131072

Process preempted involuntarily: 70
Process gave up the CPU voluntarily: 50
Major page faults: 6
Minor page faults: 13637
+++++++++++++++++++++++++++++++++++++++==> exit
bash-3.2$ ./doit cat ls -al 
total 64
drwxr-xr-x   6 KaliLine  staff    204 Sep  4 00:03 .
drwxr-xr-x  24 KaliLine  staff    816 Sep  3 23:29 ..
-rwxr-xr-x   1 KaliLine  staff  14052 Sep  4 00:01 doit
-rw-r--r--   1 KaliLine  staff   3542 Sep  3 23:56 doit.cpp
-rw-r--r--   1 KaliLine  staff   4754 Sep  4 00:04 readme.txt
-rw-r--r--   1 KaliLine  staff   3542 Sep  3 23:54 sh2.cpp
bash-3.2$ exit
exit

Script done on Fri Sep  4 00:05:01 2015
