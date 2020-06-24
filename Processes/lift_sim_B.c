#include "fileManager.h"

/******************************************************************************************
* IMPORT: argc (int), argv (char*) 
* EXPORT: none
* RETURN: 0
* ASSERTION: Creates shared memory and processes and also closes/unlinks all shared memory
*******************************************************************************************/
int main(int argc, char* argv[]) 
{
    if(argc < 3) /* Ensures that the all arguments have been inputted */
    {
        printf("Usage: lift_Sim_A <buffer size> <sleep time> \n");
    }
    else
    {
        char* bSize = argv[1]; /* Whatever is after the program name is the size of buffer  */
        char* slTime = argv[2]; /* Whatever is after the buffer size is the time to sleep for lifts  */

        if (atoi(bSize) < 1 || atoi(slTime) < 0)
        {
            printf("ERROR: Inputted buffer size or sleep time is invalid NOTE: BufferSize > 0 AND SleepTime must be positive! \n");
        }
        else
        {
            /* Clears content in sim_out to no need to delete output file after every run */
            if (remove("sim_out") == 0) { printf("\nOutput File 'sim_out' Cleared and Ready for use\n"); }

            /* Shared Memory created for all processes  */
            s = (Semaphores*)createSharedMemory(sizeof(Semaphores));
            sharedVar = (SharedVar*)createSharedMemory(sizeof(SharedVar));
            sharedVar->bufferSize = atoi(bSize);
            sharedVar->sleepTime = atoi(slTime);
            bufferArray = (Request*)createSharedMemory(sizeof(Request) * sharedVar->bufferSize);
            initSemaphores();

            sharedVar->done = FALSE;
            sharedVar->allLiftMovement = 0;

            printf("\nRunning Processes...\n");
            createProcesses();
            printf("\nProcesses complete\n");

            FILE* simOut = fopen("sim_out","a");
            /* Final Print to File statement at the end of all processes */
            if(sharedVar->done && isEmpty())
            {
                fprintf(simOut, "Total number of requests: %d\nTotal number of movements: %d", sharedVar->totalCount, sharedVar->allLiftMovement);
                fflush(simOut);
                if(sharedVar->error == TRUE)
                {
                    fprintf(simOut,"\n\nThe program has ended due to an error!\n"
                    "Please refer to command line output prompt\nNOTE:The simulation is incomplete/incorrect due to the error\n");
                    fflush(simOut);
                }
            }

            /* Any shared memory is removed/destroyed  */ 
            tearDownSem();
            unmapSharedMemory();
            fclose(simOut);
        }

    }
    return 0;
}