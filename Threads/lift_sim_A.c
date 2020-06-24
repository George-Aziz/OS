#include "fileManager.h"
#include "lift.h"

/*************************************************************************************************************
* IMPORT: argc (int), argv (char*) 
* EXPORT: none
* RETURN: 0
* ASSERTION: Creates threads and sets everything up for threads. Also closes all memory upon thread completion
***************************************************************************************************************/
int main(int argc, char* argv[]) 
{
    /* Declares All Threads and global variables used */
    pthread_t lift_R;
    pthread_t lift_1;
    pthread_t lift_2;
    pthread_t lift_3;
    done = FALSE;
    allLiftMovement = 0;

    if(argc < 3) /* Ensures that the all arguments have been inputted */
    {
        printf("Usage: lift_Sim_A <buffer size> <sleep time> \n");
    }
    else
    {
        char* bSize = argv[1]; /* Whatever is after the program name is the size of buffer  */
        char* slTime = argv[2]; /* Whatever is after the buffer size is the time to sleep for lifts  */

        bufferSize = atoi(bSize);
        sleepTime = atoi(slTime);

        if (bufferSize < 1 || sleepTime < 0)
        {
            printf("ERROR: Inputted buffer size or sleep time is invalid NOTE: BufferSize > 0 AND SleepTime must be positive! \n");
        }
        else
        {
            bufferArray = (Request**)malloc(bufferSize * sizeof(Request*)); /* Creates Buffer Array */

            /* Clears content in sim_out to no need to delete output file after every run */
            if (remove("sim_out") == 0) { printf("\nOutput File 'sim_out' Cleared and Ready for use\n"); }
        
            simOut = fopen("sim_out","w");
            printf("\nRunning Threads...\n");
            /* Producer/Consumer Threads Created */
            pthread_create(&lift_R, NULL, request, NULL);
            pthread_create(&lift_1, NULL, lift, (void*) 1);
            pthread_create(&lift_2, NULL, lift, (void*) 2);
            pthread_create(&lift_3, NULL, lift, (void*) 3);

            pthread_join(lift_R, NULL);
            pthread_join(lift_1, NULL);
            pthread_join(lift_2, NULL);
            pthread_join(lift_3, NULL);
            printf("\nThreads complete\n");
            
            /* Mutex lock not required as there are no other threads/processes running  */
            if(done && isEmpty()) /* If program complete (Always will be empty since consumers will keep doing requests till none in buffer */
            {
                fprintf(simOut, "Total number of requests: %d\nTotal number of movements: %d", totalCount, allLiftMovement);
                fflush(simOut);
                if(error == TRUE) /* If an error has occured an error message will be in sim_out and error message will be displayed in terminal */
                {
                    fprintf(simOut,"\n\nThe program has ended due to an error!\n"
                    "Please refer to command line output prompt\nNOTE:The simulation is incomplete/incorrect due to the error\n");
                    fflush(simOut);
                }
            }

            /* Frees any memory/closes file */
            free(bufferArray);
            fclose(simOut);
        }
    }
    return 0;
}