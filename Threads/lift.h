#ifndef LIFT_H
#define LIFT_H

/* Request Structure to be used by threads */
typedef struct Request
{
    int rFloor;
    int dFloor;
}Request;

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "queue.h"

/* Mutex and Condition Variables Globally Declared for all threads to use */
pthread_mutex_t lock;
pthread_cond_t cond;

/* FORWARD DECLARATIONS */
void* lift(void*);
int toReqFloor(int curFloor, int reqFloor, int destFloor);
int toDestFloor(int curFloor, int destFloor);

#endif
