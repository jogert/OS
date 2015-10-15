/* Ian Jacoway
 * irjacoway
 * CS3013 A15 Proj4
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>

#define BUF_LEN 2048 /* buffer length for semaphore initialization */
#define MAX_THREADS 15 /* max number of threads operating at once */
 					  /* attempt to avoid "too much parallelism" */

 /* To compile:
  * gcc -o maze maze.c -lpthread */

 /* mutex id */
 pthread_mutex_t mutex;  
 void BeginRegion(), EndRegion();
 void *file_threading(void *);

 /* GLOBAL VARIABLES */
 sem_t f_sem;
 struct stat stats;
 int isReg, isUreg, isText, isDir, isBad;
 int tot_reg_bytes, tot_text_bytes;


 int main(int argc, char const *argv[])
 {
 	/* start clock */
 	struct rusage times;
 	struct timeval stt;
 	struct timeval endt;
 	gettimeofday(&stt, NULL);
 	//time_t st = time(0); only does seconds
 	
 	char buf[BUF_LEN];
 	int i; // loop counter


    /* initialize couter varibles */
 	isReg = 0;
 	isUreg = 0;
 	isText = 0;
 	isDir = 0;
 	isBad = 0;
 	tot_reg_bytes = 0;
 	tot_text_bytes = 0;


 	if (argc == 1)
 	{
 		/* excute without thread code */

    	/* stdin solves argv[] pipe problem */
 		while(fgets(buf, BUF_LEN, stdin) != NULL)
 		{
 			 /* reformat */
 			if (buf[strlen(buf)-1] == '\n')
 			{
 				buf[strlen(buf)-1] = '\0';
 			}
 			/* call stat and count files */
 			if (stat(buf, &stats) == -1)
 			{
 				printf("Stat Error: bad file\n");
 				isBad++;
 			}else{
 				if (S_ISREG(stats.st_mode))
 				{
 					tot_reg_bytes += stats.st_size;
 					isReg++;

 					/* Must be initialized here inside the while
 					 * used for the loop read/check below */
 					char ch;
 					int f_type = 0; 
 					int fd = open(buf, O_RDONLY);
 					/* To read 1 character at a time */
 					for(i = 0; i < (long) stats.st_size; ++i)
 					{
 						read(fd, &ch, 1);
 						if (isspace(ch) == 0 && isprint(ch) == 0)
 						{
 							/* f_type is not text */
 							f_type = 1;
 							break;
 						}
 					}
 					/* f_type is text record stat data */
 					if (f_type == 0)
 					{
 						tot_text_bytes += stats.st_size;
 						isText++;
 					}
 					close(fd);
 				}else if (S_ISDIR(stats.st_mode))
 				{
 					isDir++;
 				}else if (S_ISFIFO(stats.st_mode) || S_ISCHR(stats.st_mode) || S_ISBLK(stats.st_mode))
 				{
 					isUreg++;
 				}else{
 					printf("File unclassied..\n");
 				}
 			}
 		}
 	}else if (argc == 3)
 	{
 		/* excute thread code */
		
		/* read max number of threads to work in parallel */
 		int max_ll_thrds = atoi(argv[2]);

 		/* limit accepted input */
 		if (max_ll_thrds > MAX_THREADS || max_ll_thrds == 0)
 		{
 			printf("Number of threads must  %d\n", MAX_THREADS);
 			exit(1);
 		}

 		/* Create file semaphore */
 		if (sem_init(&f_sem, 0, max_ll_thrds) < 0)
 		{
 			perror("sem_init");
 			exit(1);
 		}

 		/* Create mutual exlcusion of rooms */
 		if (pthread_mutex_init(&mutex, NULL) < 0) {
 			perror("pthread_mutex_init");
 			exit(1);
 		}

 		/* Create threads */
 		/* stdin solves argv[] pipe problem */
 		while(fgets(buf, BUF_LEN, stdin) != NULL){
 			/* reformat */
 			if (buf[strlen(buf)-1] == '\n')
 			{
 				buf[strlen(buf)-1] = '\0';
 			}

 			/* Make sure each the buffer isn't overwrote */
 			char* individual_buf = (char*) malloc(sizeof(char)*BUF_LEN);
 			pthread_t thrds = (pthread_t) malloc(sizeof(pthread_t)*BUF_LEN);
 			strncpy(individual_buf, buf, BUF_LEN);
 			
 			/* limiting the number of threads running to max_ll_thrds */
 			sem_wait(&f_sem);

			/* one thread per file, function they're doing, each with an individual buffer */
 			if (pthread_create(&thrds, NULL, file_threading, (void *) individual_buf) != 0)
 			{
 				perror("pthread_create");
 				exit(1);
 			}

 		}

 		/* this is takes the place of joining all threads */
 		for (i = 0; i < max_ll_thrds; ++i)
 		{
 			sem_wait(&f_sem);
 		}

 		(void) sem_destroy(&f_sem);
 		(void)pthread_mutex_destroy(&mutex);

 	}else{
 		printf("usage: <read from stdin only>\n");
 		printf("ie. ls -1d * | ./proj4\n");
 		exit(1);
 	}

 	/* Print all */
 	printf("Bad Files: %d\n", isBad);
 	printf("Directories: %d\n", isDir);
 	printf("Special Files: %d\n", isUreg);
 	printf("Regular Files: %d\n", isReg);
 	printf("Regular File Bytes: %d\n", tot_reg_bytes);
 	printf("Text Files: %d\n", isText);
 	printf("Text File Bytes: %d\n", tot_text_bytes);
 	gettimeofday(&endt, NULL);
 	int s = (endt.tv_usec/1000)-(stt.tv_usec/1000);
 	int ms = (endt.tv_sec*1000)-(stt.tv_sec*1000);
 	getrusage(RUSAGE_SELF, &times);
 	long user = (long) (times.ru_utime.tv_usec/1000) + (times.ru_utime.tv_sec*1000);
 	long cpu = (long) (times.ru_stime.tv_usec/1000) + (times.ru_stime.tv_sec*1000);
 	printf("Wall: %d milliseconds\n", s+ms);
 	printf("User: %ld milliseconds\n", user);
 	printf("CPU: %ld milliseconds\n", cpu);

 	exit(0);
 }

 void *file_threading(void *arg)
 {
 	int i;
 	char* f_name;
 	f_name = (char*)arg;
 	
 	/* call stat and count files */
 	if (stat(f_name, &stats) == -1)
 	{
 		printf("Stat Error: bad file\n");
 		BeginRegion();
 		isBad++;
 		printf("File name %s\n", f_name);
 		EndRegion();
 	}else{
 		if (S_ISREG(stats.st_mode))
 		{
 			BeginRegion();
 			tot_reg_bytes += stats.st_size;
 			isReg++;
 			EndRegion();

 			/* Must be initialized here inside the while
 			 * used for the loop read/check below */
 			char ch;
 			int i, f_type = 0; 
 			int fd = open(f_name, O_RDONLY);
 			
 			/* To read 1 character at a time */
 			for(i = 0; i < (long) stats.st_size; ++i)
 			{
 				read(fd, &ch, 1);
 				if (isspace(ch) == 0 && isprint(ch) == 0)
 				{
 					/* f_type is not text */
 					f_type = 1;
 					break;
 				}
 			}
 			/* f_type is text record stat data */
 			if (f_type == 0)
 			{
 				BeginRegion();
 				tot_text_bytes += stats.st_size;
 				isText++;
 				EndRegion();
 			}
 			close(fd);
 		}else if (S_ISDIR(stats.st_mode))
 		{
 			BeginRegion();
 			isDir++;
 			EndRegion();
 		}else if (S_ISFIFO(stats.st_mode) || S_ISCHR(stats.st_mode) || S_ISBLK(stats.st_mode))
 		{
 			BeginRegion();
 			isUreg++;
 			EndRegion();
 		}else{
 			printf("File unclassied..\n");
 		}
 	}
 	printf("File %s finished\n", f_name);
 	/* signal that thread has completed */
 	sem_post(&f_sem);
 }

 /* Mutual exclusion for threads during the open/read/close to file */
 void BeginRegion()
 {
 	pthread_mutex_lock(&mutex);
 }

 void EndRegion()
 {
 	pthread_mutex_unlock(&mutex);
 }

