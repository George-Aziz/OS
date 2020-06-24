#include "lift.h"

/******************************************************************************************
* IMPORT: liftNum (int)
* EXPORT: takes away requests from buffer
* RETURN: 0
* ASSERTION: Consumer function lift() takes out from buffer and processes it
*******************************************************************************************/
void lift(int liftNum) /* Takes in liftNum for file printing  */
{
    int count = 1, movement = 0 , totalMovement = 0, curFloor = 1, complete = FALSE;
    FILE* simOut = fopen("sim_out","a");

    while(complete == FALSE)
    {
        /* Semaphores used to process synchronization */
        sem_wait(&s->full);
        sem_wait(&s->mutex);

        if(!isEmpty())
        {
            int reqFloor = bufferArray[0].rFloor;
            int destFloor = bufferArray[0].dFloor;
            dequeue(); 
            
            movement = (abs(destFloor - reqFloor) + abs(reqFloor - curFloor));
            sharedVar->allLiftMovement = sharedVar->allLiftMovement + movement; /* allLiftMovement for end of file print statement */
            totalMovement += movement;

            fprintf(simOut, "Lift-%d Operation:\n""Previous position: Floor %d\n""Request: Floor %d to Floor %d\n" "Detail operations:\n" 
            "   Go from Floor %d to Floor %d\n" "   Go from Floor %d to Floor %d\n" "   #Movement for this request: %d\n" "   #Request: %d\n"
            "   Total #movement: %d\nCurrent position: Floor %d\n\n" ,liftNum,curFloor, reqFloor, destFloor, curFloor, reqFloor, reqFloor, destFloor, 
            movement, count, totalMovement, destFloor);
            fflush(simOut);

            /* curFloor for next iteration to know what floor lift is currently on */
            curFloor = toReqFloor(curFloor, reqFloor, destFloor);
            count++; /* Individual Request counter per lift */
        }
        
        /* Checks if the program is completely done */
        if(sharedVar->done == TRUE && isEmpty() == TRUE) { fclose(simOut); complete = TRUE; }
        sem_post(&s->mutex);
        sem_post(&s->empty);
        
        /* Sleeps to simulate real life lift */
        sleep(sharedVar->sleepTime);
    }
    sem_post(&s->full);
}

/******************************************************************************************
* IMPORT: curFloor (int), reqFloor (int), destFloor (int)
* EXPORT: none
* RETURN: destFloor (int)
* ASSERTION: Function to go to reqFloor (floor that request has been made from)
*******************************************************************************************/
int toReqFloor(int curFloor, int reqFloor, int destFloor)
{
    if (curFloor != reqFloor)
    {
        curFloor = reqFloor;
    }
    return toDestFloor(curFloor, destFloor);
}

/******************************************************************************************
* IMPORT: curFloor (int), destFloor (int)
* EXPORT: none
* RETURN: curFloor
* ASSERTION: Function to go to destFloor (floor that request wants to reach)
*******************************************************************************************/
int toDestFloor(int curFloor, int destFloor)
{
    curFloor = destFloor;
    return curFloor;
}