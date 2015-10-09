/* shell.cpp Ian J */

#include <iostream>
using namespace std;
#include <unistd.h>
#include <sys/wait.h>
/* for getrusage() */
#include <sys/time.h>
#include <sys/resource.h>

extern char **environ;		/* environment info */

int main(int argc, char **argv){

/* collect usage data variables */
    struct rusage usage;
    struct timeval userStart, userEnd;
    struct timeval sysStart, sysEnd;
    struct timeval day;
    float dayStart;
    float dayEnd;
    int invol;
    int vol;
    float maj;
    float min;

/* shell input varibles */
    char *argvNew[33];
    char com[128];
    int pid;
    int i, k;
    int status;
    char* token;
/* Start stats */
    gettimeofday(&day, NULL);  
    dayStart = day.tv_sec*1000;//+(day.tv_usec/1000.0);

    getrusage(RUSAGE_CHILDREN, &usage);
    sysStart = usage.ru_stime;
    userStart = usage.ru_utime;
    
    while(1){
        /* at comline execution */
        if (argc > 1){

            strcpy( com, "/bin/");
            strcat(com, argv[1]);
            argvNew[0] = com;
            for (i = 1; i < argc; ++i)
            {
                argvNew[i] = argv[i+1];
            }
            /* child process */
            argvNew[i+1] = NULL;

            if (execve(argvNew[0], argvNew, environ) < 0) {
                cerr << "Execve error\n";
                exit(1);
            }

        }else{
            cout << "==> ";
            fgets (com, 128, stdin);
            com[strlen(com)-1]= '\0';
            token = strtok(com, " ");
            k = 0;

            while(token != NULL){
                argvNew[k++] = token;
                token = strtok(NULL, " ");
            }
            argvNew[k] = NULL;

                
        }
        if ((pid = fork()) < 0) {
            cerr << "Fork error\n";
            exit(1);
        } else if (pid == 0){
            

            if (execvp(argvNew[0], argvNew) < 0) {
                    /* cerr << "Execve error\n";
                        conflicts with a proper exit */
            }
            exit(0);
        }else{
            /* parent process */
            waitpid(pid, &status, 0);
            if (strcmp(argvNew[0], "cd") == 0){
                chdir(argvNew[1]);
            }

            if (strcmp(argvNew[0], "exit") == 0){
                exit(0);
            }

    /* Store stats */
            gettimeofday(&day, NULL);  
            dayEnd = day.tv_sec*1000;//+(day.tv_usec/1000.0);

            getrusage(RUSAGE_CHILDREN, &usage);
            sysEnd = usage.ru_stime;
            userEnd = usage.ru_utime;
            invol = usage.ru_nivcsw;
            vol = usage.ru_nvcsw;
            maj = usage.ru_majflt;
            min = usage.ru_minflt;
        /* Print stats data */
            cout << "+++++++++++++++++STATS++++++++++++++++";
            cout << "\n\nUser time: " << userEnd.tv_sec*1000  << "." << userEnd.tv_usec*1000 << "\n";
            cout << "System time: " << sysEnd.tv_sec*1000  << "." << sysEnd.tv_usec*1000 << "\n";
            cout << "Wall-Clock elapsed: " << (dayEnd - dayStart) << "\n\n";
            
            cout << "Process preempted involuntarily: " << invol << "\n";
            cout << "Process gave up the CPU voluntarily: " << vol << "\n";
            cout << "Major page faults: " << maj << "\n";
            cout << "Minor page faults: " << min << "\n";
            cout << "+++++++++++++++++++++++++++++++++++++++";
        }

    /* exit if commands entered at comline */
        if (argc > 1){
            exit(0);
        }
    }
}


