#include "queue.h"

/******************************************************************************************
* IMPORT: none
* EXPORT: none
* RETURN: boolean (int)
* ASSERTION: Checks if buffer is Empty
*******************************************************************************************/
int isEmpty()
{
    int boolean = FALSE; //Value that returns true/false depending if array is full or empty
    if(sharedVar->numRequests == 0)
    {
        boolean = TRUE;
    }
    return boolean;
}

/******************************************************************************************
* IMPORT: none
* EXPORT: none
* RETURN: boolean (int)
* ASSERTION: Checks if buffer is full
*******************************************************************************************/
int isFull()
{
    int boolean = FALSE; //Value that returns true/false depending if array is full or empty
    if (sharedVar->numRequests == sharedVar->bufferSize)
    {
        boolean = TRUE;
    }
    return boolean;
}

/******************************************************************************************
* IMPORT: none
* EXPORT: new request in buffer
* RETURN: void
* ASSERTION: insert a new request into the buffer
*******************************************************************************************/
void enqueue (int reqFloor, int destFloor)
{
    if(isFull() == FALSE) /* Only insert if buffer is not full */
    {
        bufferArray[sharedVar->numRequests].rFloor = reqFloor;
        bufferArray[sharedVar->numRequests].dFloor = destFloor;
        sharedVar->numRequests = sharedVar->numRequests + 1; /* Increments buffer count */
    }
}

/******************************************************************************************
* IMPORT: none
* EXPORT: remove request from buffer
* RETURN: void
* ASSERTION: Function to remove a request from buffer
*******************************************************************************************/
void dequeue ()
{
    if (isEmpty() == FALSE) /* Only remove if buffer is not empty */
    {
        for (int i = 0; i < sharedVar->numRequests-1;i++) /* Shuffles all buffer elements 1 position to the front (-1 to all elements) */
        {
            bufferArray[i] = bufferArray[i+1]; 
        }
        sharedVar->numRequests = sharedVar->numRequests -1; /* Decrements buffer count */
    }
} 
