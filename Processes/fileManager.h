#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "lift.h"
#include "queue.h"
#include "processes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

/* False/True Definitions for later usage in file */
#define FALSE 0
#define TRUE !FALSE
#define INPUTSIZE 3

/* FORWARD DECLARATIONS */
void* request();
void readLine(FILE* file);

#endif
