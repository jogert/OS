/* Ian J & Derek M */

Script started on Thu 17 Sep 2015 11:55:47 PM EDT
dmmcmaster@derek:~/Documents/proj2$ ./testphas2 
	syscall2: 0
		State          : 0
		Pid            : 3319
		Parent  Pid    : 3307
		Yougest Kid Pid: 562535630
		Younger Sib Pid: -1
		Older   Sib Pid: 1
		Uid            : 1000

	Times:
		Start     : 924048254238
		User      : 4107559552
		System    : 4107575552
		Kid User  : 4094279552
		Kid system: 4094295552

dmmcmaster@derek:~/Documents/proj2$ sleep 2 & ./testphas2 & sleep 2 
[1] 3321
[2] 3322
[3] 3323
	syscall2: 0
		State          : 0
		Pid            : 3322
		Parent  Pid    : 3307
		Yougest Kid Pid: 320248182
		Younger Sib Pid: 3323
		Older   Sib Pid: 3321
		Uid            : 1000

	Times:
		Start     : 929723068405
		User      : 4094247552
		System    : 4094263552
		Kid User  : 4160839552
		Kid system: 4160855552

[1]   Done                    sleep 2
[2]-  Done                    ./testphas2
[3]+  Done                    sleep 2
dmmcmaster@derek:~/Documents/proj2$ sleep 2 & ./testphas2 &
[1] 3325
[2] 3326
	syscall2: 0
		State          : 0
		Pid            : 3326
		Parent  Pid    : 3307
		Yougest Kid Pid: 1100746672
		Younger Sib Pid: -1
		Older   Sib Pid: 3325
		Uid            : 1000

	Times:
		Start     : 986118677069
		User      : 4107559552
		System    : 4107575552
		Kid User  : 4094279552
		Kid system: 4094295552

[1]-  Done                    sleep 2
[2]+  Done                    ./testphas2
Script done on Thu 17 Sep 2015 11:57:19 PM EDT
