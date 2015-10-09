/* Ian J */
#Rats as threads navigate maze room semaphores

**Tests compiled in Ubuntu linux environment**

To compile type:
	make <enter>
To run type:
	./maze <num of rats> <i, d, or n>

If desired, to run bash script tests type:
	sh tests.sh
Script started on Fri 02 Oct 2015 01:15:26 AM EDT
cali@dude-Righteous:~/Desktop/3proj$ sh tests.sh 
clean
/bin/rm -f *.o core maze
make
gcc maze.c -o maze -lpthread -lrt 
usage: ./maze <max # rats is: 5> <algorithm type(i/d)>
alg: inorder
		is thinking..
Rat 0 took 5 in maze.
Room 0 [3 1] 0 0 1; 
Room 1 [2 2] 0 1 3; 
Room 2 [1 2] 0 3 5; 
Actual Trav: 5 Ideal Trav: 5
alg: distributed
		is thinking..
Rat 0 took 5 in maze.
Room 0 [3 1] 0 0 1; 
Room 1 [2 2] 0 1 3; 
Room 2 [1 2] 0 3 5; 
Actual Trav: 5 Ideal Trav: 5
alg: non-blocking
		is thinking..
Rat 0 took 5 in maze.
Room 0 [3 1] 0 0 1; 
Room 1 [2 2] 0 1 3; 
Room 2 [1 2] 0 3 5; 
Actual Trav: 5 Ideal Trav: 5
alg: inorder
		is thinking..
Rat 1 took 5 in maze.
Rat 0 took 7 in maze.
Room 0 [3 1] 0 0 1; 1 0 1; 
Room 1 [2 2] 0 1 3; 1 1 3; 
Room 2 [1 2] 0 5 7; 1 3 5; 
Actual Trav: 12 Ideal Trav: 10
alg: distributed
		is thinking..
Rat 1 took 5 in maze.
Rat 0 took 6 in maze.
Room 0 [3 1] 0 0 1; 1 4 5; 
Room 1 [2 2] 0 1 3; 1 0 2; 
Room 2 [1 2] 0 4 6; 1 2 4; 
Actual Trav: 11 Ideal Trav: 10
alg: non-blocking
		is thinking..
Rat 1 took 5 in maze.
Rat 0 took 6 in maze.
Room 0 [3 1] 0 0 1; 1 4 5; 
Room 1 [2 2] 0 1 3; 1 0 2; 
Room 2 [1 2] 0 4 6; 1 2 4; 
Actual Trav: 11 Ideal Trav: 10
alg: inorder
		is thinking..
Rat 2 took 5 in maze.
Rat 1 took 7 in maze.
Rat 0 took 9 in maze.
Room 0 [3 1] 0 0 1; 1 0 1; 2 0 1; 
Room 1 [2 2] 0 3 5; 1 1 3; 2 1 3; 
Room 2 [1 2] 0 7 9; 1 5 7; 2 3 5; 
Actual Trav: 21 Ideal Trav: 15
alg: distributed
		is thinking..
Rat 1 took 5 in maze.
Rat 2 took 5 in maze.
Rat 0 took 6 in maze.
Room 0 [3 1] 0 0 1; 1 4 5; 2 2 3; 
Room 1 [2 2] 0 1 3; 1 0 2; 2 3 5; 
Room 2 [1 2] 0 4 6; 1 2 4; 2 0 2; 
Actual Trav: 16 Ideal Trav: 15
alg: non-blocking
		is thinking..
Rat 2 took 5 in maze.
Rat 1 took 5 in maze.
Rat 0 took 6 in maze.
Room 0 [3 1] 0 0 1; 1 4 5; 2 2 3; 
Room 1 [2 2] 0 1 3; 1 0 2; 2 3 5; 
Room 2 [1 2] 0 4 6; 1 2 4; 2 0 2; 
Actual Trav: 16 Ideal Trav: 15
alg: inorder
		is thinking..
Rat 3 took 5 in maze.
Rat 2 took 7 in maze.
Rat 1 took 9 in maze.
Rat 0 took 11 in maze.
Room 0 [3 1] 0 1 2; 1 0 1; 2 0 1; 3 0 1; 
Room 1 [2 2] 0 3 5; 1 3 5; 2 1 3; 3 1 3; 
Room 2 [1 2] 0 9 11; 1 7 9; 2 5 7; 3 3 5; 
Actual Trav: 32 Ideal Trav: 20
alg: distributed
		is thinking..
Rat 2 took 5 in maze.
Rat 1 took 5 in maze.
Rat 3 took 6 in maze.
Rat 0 took 8 in maze.
Room 0 [3 1] 0 0 1; 1 4 5; 2 2 3; 3 0 1; 
Room 1 [2 2] 0 2 4; 1 0 2; 2 3 5; 3 1 3; 
Room 2 [1 2] 0 6 8; 1 2 4; 2 0 2; 3 4 6; 
Actual Trav: 24 Ideal Trav: 20
alg: non-blocking
		is thinking..
Rat 2 took 5 in maze.
Rat 1 took 5 in maze.
Rat 0 took 6 in maze.
Rat 3 took 8 in maze.
Room 0 [3 1] 0 0 1; 1 4 5; 2 2 3; 3 0 1; 
Room 1 [2 2] 0 2 4; 1 0 2; 2 3 5; 3 1 3; 
Room 2 [1 2] 0 4 6; 1 2 4; 2 0 2; 3 6 8; 
Actual Trav: 24 Ideal Trav: 20
alg: inorder
		is thinking..
Rat 3 took 5 in maze.
Rat 4 took 7 in maze.
Rat 2 took 9 in maze.
Rat 1 took 11 in maze.
Rat 0 took 13 in maze.
Room 0 [3 1] 0 1 2; 1 1 2; 2 0 1; 3 0 1; 4 0 1; 
Room 1 [2 2] 0 5 7; 1 3 5; 2 3 5; 3 1 3; 4 1 3; 
Room 2 [1 2] 0 11 13; 1 9 11; 2 7 9; 3 3 5; 4 5 7; 
Actual Trav: 45 Ideal Trav: 25
alg: distributed
		is thinking..
Rat 4 took 5 in maze.
Rat 3 took 6 in maze.
Rat 2 took 6 in maze.
Rat 1 took 9 in maze.
Rat 0 took 10 in maze.
Room 0 [3 1] 0 0 1; 1 8 9; 2 2 3; 3 0 1; 4 4 5; 
Room 1 [2 2] 0 2 4; 1 0 2; 2 4 6; 3 2 4; 4 0 2; 
Room 2 [1 2] 0 8 10; 1 6 8; 2 0 2; 3 4 6; 4 2 4; 
Actual Trav: 36 Ideal Trav: 25
alg: non-blocking
		is thinking..
Rat 1 took 5 in maze.
Rat 3 took 6 in maze.
Rat 2 took 6 in maze.
Rat 0 took 8 in maze.
Rat 4 took 10 in maze.
Room 0 [3 1] 0 0 1; 1 4 5; 2 2 3; 3 0 1; 4 2 3; 
Room 1 [2 2] 0 2 4; 1 0 2; 2 4 6; 3 2 4; 4 0 2; 
Room 2 [1 2] 0 6 8; 1 2 4; 2 0 2; 3 4 6; 4 8 10; 
Actual Trav: 35 Ideal Trav: 25
Script done on Fri 02 Oct 2015 01:17:31 AM EDT
