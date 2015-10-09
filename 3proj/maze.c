/* Ian J */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>

#include "amze.h"       /* include the header amze.h */

#define MAXROOMS 8    /* maxium number of rooms */
#define MAXRATS 5    /* maxium number of rats */
#define BUF_LEN 128 /* buffer length for semaphore initialization */

/* To compile:
 * gcc -o maze maze.c -lpthread */


/* mutex id */
 pthread_mutex_t mutex;  
 void BeginRegion(), EndRegion();
 void *rat(void *);

/* GLOBAL VARIABLES */

 time_t start_OP;
 char alg_type;
 int ctr_rms;
/* array of room visitors books */
 struct vbentry RoomVB[MAXROOMS][MAXRATS];
 int rm_info[MAXROOMS][MAXRATS];
 sem_t rooms[MAXROOMS];

 int main(int argc, char const *argv[])
 {
    /* Start the clock */
    start_OP = time(0);
    /* Initialize variables */
    ctr_rms = 0;
    int ideal_trav = 0;
    int trav_time = 0;
    int num_rats, capcity, delay;
    /* loop ctrs */
    int i, j, w, x, y, z;

    /* Exclude misusages */
    if (argc != 3)
    {
        printf("usage: ./maze <max # rats is: %d> <algorithm type(i/d)>\n", MAXRATS);
        exit(1);
    }

    /* Take in inputs */
    sscanf(argv[1], "%d", &num_rats);
    sscanf(argv[2], "%c", &alg_type);

    /* Check num_rats after it exists */
    if (num_rats > MAXRATS)
    {
        printf("usage: ./maze <max # rats is: %d> <algorithm type(i/d)>\n", MAXRATS);
        exit(1);
    }

    /* Print algorithm types */
    if (alg_type == 'i'|| alg_type == 'I')
    {
        printf("alg: inorder\n\t\tis thinking..\n");
    }else if (alg_type == 'd'|| alg_type == 'D')
    {
        printf("alg: distributed\n\t\tis thinking..\n");
    }else if (alg_type == 'n' || alg_type == 'N')
    {
        printf("alg: non-blocking\n\t\tis thinking..\n");
    }else{
        printf("usage: ./maze <max # rats is: %d> <algorithm type(i/d)>\n", MAXRATS);
        exit(1);
    }

    /* Read from file */
    FILE *inFile = fopen("rooms","r");
    char buf[BUF_LEN];

    /* Error on opening file */
    if(inFile == NULL)
    {
        printf("No file named rooms in the directory!\n");
        exit(1);
    }

    while (fgets (buf, BUF_LEN, inFile) != NULL && ctr_rms < MAXROOMS)
    {
        /* Read the capacities and delays from "rooms" */
        sscanf(buf, "%d %d\n", &capcity, &delay);
        rm_info[ctr_rms][0] = capcity;
        rm_info[ctr_rms][1] = delay;

        /* part one calculate ideal_trav */
        ideal_trav += rm_info[ctr_rms][1];

        /* Make dem roomz */
        if (sem_init(&rooms[ctr_rms], 0, rm_info[ctr_rms][0]) < 0)
        {
            perror("sem_init");
            exit(1);
        }
        ctr_rms++;
    }

    /* Create deez ratz */
    pthread_t rats[MAXRATS];
    for (i = 0; i < num_rats; ++i)
    {
        if (pthread_create(&rats[i], NULL, rat, (void *) i) != 0)
        {
            perror("pthread_create");
            exit(1);
        }
    }

    /* Join all rats into one monster: Ratcula the blood sucking canabal */
    for (j = 0; j < num_rats; ++j)
    {
        (void)pthread_join(rats[j], NULL);
    }

    /* Create mutual exlcusion of rooms */
    if (pthread_mutex_init(&mutex, NULL) < 0) {
        perror("pthread_mutex_init");
        exit(1);
    }

    /* Done computing so now we can burn the threads */
    //(void)sem_destroy(&rooms); throws warning but is valid
    (void)pthread_mutex_destroy(&mutex);

    /* Print eveeeeerything */
    for (w = 0; w < ctr_rms; ++w)
    {
        printf("Room %d [%d %d] ", w, rm_info[w][0], rm_info[w][1]);
        for (x = 0; x < num_rats; ++x)
        {
            printf("%d %d %d; ", RoomVB[w][x].iRat, RoomVB[w][x].tEntry, RoomVB[w][x].tDep);
        }
        printf("\n");
    }

    /* Part 2 of calculating ideal_trav */
    ideal_trav = ideal_trav * num_rats;

    /* set actual traversal time of the entire maze by all rats */
    int max_depart = -1;
    for (y = 0; y < num_rats; ++y)
    {
        /* reset the max departure for each rat */
        max_depart = -1;
        /* find max departure of each rat */
        for(z = 0; z < ctr_rms; z++){
            if(max_depart < RoomVB[z][y].tDep)
            {
                max_depart = RoomVB[z][y].tDep;
            }
        }
        /* add all the maxes */
        trav_time += max_depart;
    }
    printf("Actual Trav: %d Ideal Trav: %d\n", trav_time, ideal_trav);

    return 0;
}

/* Algorthims */
void *rat(void *arg)
{
    int i, j, ratName;
    ratName = (int)arg;

    /* inorder code */
    if (alg_type == 'i'|| alg_type =='I')
    {
        for ( i = 0; i < ctr_rms; i++)
        {
            EnterRoom(ratName, i);
        }
    /* distributed code */
    } else if (alg_type == 'd'|| alg_type == 'D')
    {
        /* Decide which room to start rat in */
        int rat_placement = ratName % ctr_rms;
        for (i = 0; i < ctr_rms; i++)
        {
            EnterRoom(ratName, rat_placement);
            /* If room is full try the next room */
            if ( rat_placement < ctr_rms-1)
            {
                rat_placement++;
            }else{
                rat_placement = 0;
            }
        }
    /* non-blocking code */
    }else if (alg_type == 'n' || alg_type == 'N')
    {
        /* Decide which room to start rat in */
        int rat_placement = ratName % ctr_rms;
        /* Makes sure rat enters all the rooms then exits while loop */
        int ctr_visited = 0;
        /* Make an array to keep track of rat's visited rooms */
        int visited[rat_placement];
        /* Intialize visited values */
        for (i = 0; i < ctr_rms; i++)
        {
            visited[i] = 0;
        }
        /* while rat hasn't visited every room */
        while(ctr_visited < ctr_rms)
        {
            /* check if rat has visited room & try to enter if hasn't */
            if (visited[rat_placement] == 0)
            {
                if (TryToEnterRoom(ratName, rat_placement) == 0)
                {
                    visited[rat_placement] = 1;
                    ctr_visited++;
                }
            }
            /* if room is full try next room */
            if (rat_placement < ctr_rms)
            {
                rat_placement++;
            }
            else
            {
                rat_placement = 0;
            }
        } /* based on distributed alg, but is slightly faster */

        /* non-blocking based on inorder alg, but slightly faster */
        /* It's real slow compared to implementation above */
        // for ( i = 0; i < ctr_rms; i++)
        // {
        //     while(TryToEnterRoom(ratName, i) == -1);
        // }
    }
    /* Print rattata as it finishes the maze */
    int max_depart = -1;
    for (j = 0; j < ctr_rms; ++j)
    {
        if (max_depart < RoomVB[j][ratName].tDep)
        {
            max_depart = RoomVB[j][ratName].tDep;
        }
    }
    printf("Rat %d took %d in maze.\n", ratName, max_depart);
}   

/* See if rat could enter the room, then enter */
int TryToEnterRoom(int iRat,int iRoom)
{
    if (sem_trywait(&rooms[iRoom]) == -1)
    {
        return -1;
    }
    time_t timeNow = time(0);
    sleep(rm_info[iRoom][1]);
    LeaveRoom(iRat, iRoom, (int) timeNow);
    return 0;
}
/* Let rats into the room or not */
void EnterRoom(int iRat, int iRoom)
{
    sem_wait(&rooms[iRoom]);
    time_t timeNow = time(0);
    sleep(rm_info[iRoom][1]);
    LeaveRoom(iRat, iRoom, (int) timeNow);

}

/* Have the rats leave the room */
void LeaveRoom(int iRat, int iRoom, int tEnter)
{
    BeginRegion();
    RoomVB[iRoom][iRat].iRat = iRat;
    RoomVB[iRoom][iRat].tEntry = tEnter - start_OP;
    time_t timeNow = time(0);
    RoomVB[iRoom][iRat].tDep = (int) timeNow - start_OP;
    EndRegion();
    sem_post(&rooms[iRoom]);
}
/* Establishes mutual exclusion for rats while writing in the vistor book */
void BeginRegion()
{
    pthread_mutex_lock(&mutex);
}

void EndRegion()
{
    pthread_mutex_unlock(&mutex);
}
