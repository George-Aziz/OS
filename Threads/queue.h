#ifndef QUEUE_H
#define QUEUE_H

#include "lift.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "fileManager.h"

/* DEFINE TRUE/FALSE */
#define FALSE 0
#define TRUE !FALSE

/* FORWARD DECLARATIONS */
int isEmpty();
int isFull();
void enqueue (Request* request);
void dequeue ();

#endif