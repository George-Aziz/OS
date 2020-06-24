#include "fileManager.h"
#define _GNU_SOURCE 1

/**************************************************************************************
* IMPORT: none
* EXPORT: none
* RETURN: NULL
* ASSERTION: Producer Method request() opens file to read
***************************************************************************************/
void* request ()
{
    FILE* file;
    file = fopen("sim_input", "r"); /* Opens input stream for settings file */
    if (file == NULL) 
    { 
        perror("ERROR: Unable to open input_sim file!");
    }
    else
    {
        readLine(file);
    }
    /* Only closes the file if it has been opened */
    fclose(file); /* Makes sure the file is closed at the end */
    return NULL;
}

/**************************************************************************************
* IMPORT: FILE* 
* EXPORT: Creates a request per line and inputs into shared buffer
* RETURN: none
* ASSERTION: reads sim_input file per line with process synchronisation
***************************************************************************************/
/* Aziz, George. (2019). UCP Assignment. */
/* The basic file I/O reading and error checking approach has been taken from my UCP assignment last semester (2019) */
void readLine (FILE* file)
{
    int numElements, reqFloor, destFloor; 
    char destStr[INPUTSIZE];
    char* endPtr;
    sharedVar->error = FALSE; 
    sharedVar->totalCount = 0;
    int prodComplete = FALSE;
    
    FILE* simOut = fopen("sim_out","a");
    /* While not done and no error has been found */ 
    while(!prodComplete) 
    {
        /* Semaphores to ensure process synchronization */
        sem_wait(&s->empty);
        sem_wait(&s->mutex);

        /* Read a line from file */
        numElements = fscanf(file, "%d %s\n", &reqFloor ,destStr);
        destFloor = strtol(destStr, &endPtr, 10);
        if (*endPtr == '\0' && numElements == 2)
        {
            if (reqFloor > 0 && destFloor > 0 && reqFloor <= 20 && destFloor <= 20) /* Ensures only Levels from 1 - 20 */
            {
                /* Creates a new request every time a new request needs to be made and puts into buffer */
                enqueue(reqFloor, destFloor);
                
                sharedVar->totalCount = sharedVar->totalCount + 1; /* totalCount for end check if there are minimum of 50 requests or less than 100 */

                fprintf(simOut,"----------------------------------\nNew Lift Request From Floor %d to Floor %d\nRequest No: %d\n"
                "----------------------------------\n\n", reqFloor, destFloor, sharedVar->totalCount);
                fflush(simOut); 
            }
            else /* If one of the requests found in sim_input is invalid an error has been found */
            {
                sharedVar->done = TRUE; 
                sharedVar->error = TRUE;
                /* Errors print to terminal for user */
                printf("\nERROR: Each request must be made from Level 1 - 20 only!\nPlease wait for consumer processes to finish!\n"); 
            }
        }
        else
        { 
            sharedVar->done = TRUE;
            if (numElements != EOF) /* Fscanf also takes in EOF, so this prints only if a line is invalid in the actual file */
            {
                printf("\nERROR: One request is invalid due to not using integers!\nPlease wait for consumer processes to finish!\n");
                sharedVar->error = TRUE;
            }
            else /* If the end of file has reached, check total number of requests inputted */
            {
                /* If the total amount of requests read are less than 50 or more than 100 */
                if (sharedVar->totalCount < 50 || sharedVar->totalCount > 100) 
                {
                    printf("\nERROR: Only 50 - 100 Requests are allowed in file!\nPlease wait for consumer processes to finish!\n");
                    sharedVar->error = TRUE;
                }
            }
        }
        if(sharedVar->done == TRUE || sharedVar->error == TRUE) { prodComplete = TRUE; fclose(simOut); }

        /* After a request has been inputted semaphores must signal for consumers or next producer iteration */
        sem_post(&s->mutex);
        sem_post(&s->full);
    }
}
