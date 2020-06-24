#ifndef LIFT_H
#define LIFT_H

/* Request Function for Producer/Consumers */
typedef struct Request
{
    int rFloor;
    int dFloor;
}Request;

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

/* FORWARD DECLARATIONS */
void lift(int);
int toReqFloor(int curFloor, int reqFloor, int destFloor);
int toDestFloor(int curFloor, int destFloor);

#endif
