#include "fileManager.h"

/**************************************************************************************
* IMPORT: none
* EXPORT: none
* RETURN: NULL
* ASSERTION: Producer Method request() opens file to read
***************************************************************************************/
void* request (void* import)
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
    int prodComplete = FALSE;
    error = FALSE; 
    totalCount = 0;

    /* While not done and no error has been found */ 
    while(!prodComplete) 
    {
        pthread_mutex_lock(&lock); /* Locks here before any shared variable with other threads are accessed */

        /* While the buffer is queue, the thread will sleep until signalled to wake up and enqueue */
        while(isFull()) { pthread_cond_wait(&cond, &lock); }

        /* Read a line from file */
        numElements = fscanf(file, "%d %s\n", &reqFloor ,destStr);
        destFloor = strtol(destStr, &endPtr, 10);
        if (*endPtr == '\0' && numElements == 2)
        {
            if (reqFloor > 0 && destFloor > 0 && reqFloor <= 20 && destFloor <= 20) /* Ensures only Levels from 1 - 20 */
            {
                /* Creates a new request every time a new request needs to be made */
                Request* request = (Request*)malloc(sizeof(Request));
                request->rFloor = reqFloor;
                request->dFloor = destFloor;

                enqueue(request);
                totalCount = totalCount + 1; /* totalCount for end check if there are minimum of 50 requests or less than 100 */
                fprintf(simOut,"----------------------------------\nNew Lift Request From Floor %d to Floor %d\nRequest No: %d\n"
                "----------------------------------\n\n", reqFloor, destFloor, totalCount);
                fflush(simOut);
            }
            else /* If request has an error */
            {
                done = TRUE;
                error = TRUE;
                printf("\nERROR: Each request must be made from Level 1 - 20 only!\nPlease wait for consumer threads to finish!\n");
            }
        }
        else
        { 
            done = TRUE;
            if (numElements != EOF) /* Fscanf also takes in EOF, so this prints only if a line is invalid in the actual file */
            {
                printf("\nERROR: One request is invalid due to not using integers!\nPlease wait for consumer threads to finish!\n");
                error = TRUE;
            }
            else /* If the end of file has reached then all other error checking will proceed */
            {
                if (totalCount < 50 || totalCount > 100) /* If the total amount of requests read are less than 50 or more than 100 */
                {
                    printf("\nERROR: Only 50 - 100 Requests are allowed in file!\nPlease wait for consumer threads to finish!\n");
                    error = TRUE;
                }
            }
        }
        if (done == TRUE || error == TRUE) { prodComplete = TRUE; }
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
}
