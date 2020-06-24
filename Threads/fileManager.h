#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "lift.h"
#include "queue.h"
/* False/True Definitions for later usage in file */
#define FALSE 0
#define TRUE !FALSE
#define INPUTSIZE 3

/* Global Variables */
int bufferSize;
int sleepTime;
int numRequests;
int done;
int allLiftMovement;
int totalCount;
int error;
Request** bufferArray;
FILE* simOut;

/* FORWARD DECLARATIONS */
void* request(void*);
void readLine(FILE* file);

#endif
