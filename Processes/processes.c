#include "processes.h"

/******************************************************************************************
* IMPORT: none
* EXPORT: sets value of semaphores
* RETURN: none
* ASSERTION: Initialises Semaphores
*******************************************************************************************/
void initSemaphores()
{
    sem_init(&s->empty, 1, sharedVar->bufferSize);
    sem_init(&s->mutex, 1, 1);
    sem_init(&s->full, 1, 0);
}

/******************************************************************************************
* IMPORT: none
* EXPORT: none
* RETURN: none
* ASSERTION: Once program is complete semaphores are required to be destroyed 
*******************************************************************************************/
void tearDownSem()
{
    sem_destroy(&s->empty);
    sem_destroy(&s->mutex);
    sem_destroy(&s->full);
}

/******************************************************************************************
* IMPORT: size (size_t)
* EXPORT: none
* RETURN: mmap to shared memory
* ASSERTION: Creates Shared Memory for processes (Replaces Malloc)
*******************************************************************************************/
void* createSharedMemory(size_t size)
{
    int protection = PROT_READ | PROT_WRITE;
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    return mmap(NULL,size,protection,visibility,-1,0);
}

/******************************************************************************************
* IMPORT: none
* EXPORT: none
* RETURN: none
* ASSERTION: Removes Shared Memory
*******************************************************************************************/
void unmapSharedMemory()
{
    munmap(bufferArray, sizeof(Request) * sharedVar->bufferSize);
    munmap(sharedVar, sizeof(SharedVar));
    munmap(s, sizeof(Semaphores));
}


/******************************************************************************************
* IMPORT: none
* EXPORT: none
* RETURN: none
* ASSERTION: Creates 4 child processes for producer/consumers
*******************************************************************************************/
void createProcesses()
{
    pid_t pids[4];
    int i;
    int n = 4;

    for (i = 0; i < n; ++i) 
    {
        if ((pids[i] = fork()) < 0) /* If an error occured while forking exit program */
        {
            perror("Fork Error!");
            abort(); 
        } 
        else if (pids[i] == 0) /* If the process is a child */
        {
            if (i == 0) /* If this is the first iteration call request() which is Lift_R (Producer) */
            {
                request();
            }
            else if (i != 0) /* If its not first iteration do the consumer lift() processes */
            {
                lift(i);
            }
            exit(0); /* Once processes are done they must exit here */
        }
    }

    /* Wait for children to exit. */
    int status;
    pid_t pid;
    while (n > 0) /* Ensures parent process waits for each child process */
    {
        pid = wait(&status);
        --n;
    }
}
