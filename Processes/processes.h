#ifndef PROCESSES_H
#define PROCESSES_H

#include <semaphore.h>
/* All variables that will be shared between processes */
typedef struct SharedVar
{
    int numRequests;
    int allLiftMovement;
    int totalCount;
    int done;
    int error;
    int sleepTime;
    int bufferSize;
}SharedVar;

/* Struct for semaphores that will be used in program */
typedef struct Semaphores
{
    sem_t empty;
    sem_t mutex;
    sem_t full;
}Semaphores;

#include "fileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

/* Global Variables Structs */
Semaphores* s;
SharedVar* sharedVar;
Request* bufferArray;

/* FORWARD DECLARATIONS */
void initSemaphores();
void tearDownSem();
void* createSharedMemory(size_t);
void unmapSharedMemory();
void createProcesses();
#endif