#include "lift.h"

/*************************************************************************************************************
* IMPORT: liftNum (void*)
* EXPORT: none
* RETURN: NULL (void*)
* ASSERTION: Consumer Function lift() reads request from buffer and processes it
***************************************************************************************************************/
void* lift(void* liftNum)
{
    int count = 1, movement = 0 , totalMovement = 0, lift = (int)liftNum, curFloor = 1, complete = FALSE;

    while(!complete)  
    {
        sleep(sleepTime); /* Sleep to simulate real life lifts */
        pthread_mutex_lock(&lock); /* Mutex Lock to have synchronisation and prevent race conditions */

        /* While buffer is empty and the program isn't finished wait until producer fills up buffer */
        while(isEmpty() && !done) { pthread_cond_wait(&cond,&lock); }

        if (!isEmpty()) /* If statement is here incase last thread reaches this part when everything is completely done */
        {
            int reqFloor = bufferArray[0]->rFloor;
            int destFloor = bufferArray[0]->dFloor;
            dequeue(); /* Removes request once request has been acquired */
            
            movement = (abs(destFloor - reqFloor) + abs(reqFloor - curFloor));
            allLiftMovement = allLiftMovement + movement;
            totalMovement += movement;

            fprintf(simOut, "Lift-%d Operation:\n""Previous position: Floor %d\n""Request: Floor %d to Floor %d\n" "Detail operations:\n" 
            "   Go from Floor %d to Floor %d\n" "   Go from Floor %d to Floor %d\n" "   #Movement for this request: %d\n" "   #Request: %d\n"
            "   Total #movement: %d\n" ,lift,curFloor, reqFloor, destFloor, curFloor, reqFloor, reqFloor, destFloor, movement, count, totalMovement);
            fflush(simOut);
            
            curFloor = toReqFloor(curFloor, reqFloor, destFloor); /* Determine Current Floor for next iteration */
            count++; /* Individual Request Counter per lift for file printing */
        }
        
        /* If the program is completely finished then this will be last iteration */
        if(done == TRUE && isEmpty() == TRUE) { complete = TRUE; }

        /* Consumer is finished, Unlocks and signals the condition for any other thread */
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
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
    fprintf(simOut,"Current position: Floor %d\n\n",curFloor);
    fflush(simOut);
    return curFloor;
}