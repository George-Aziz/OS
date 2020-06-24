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
    if(numRequests == 0)
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
    if (numRequests == bufferSize)
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
void enqueue (Request* request)
{
    if(isFull() == FALSE)
    {
        bufferArray[numRequests] = request;
        numRequests++;
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
    Request* frontVal = NULL;
    if(isEmpty() == FALSE)
    {
        frontVal = bufferArray[0];
        for (int i = 0; i < numRequests-1;i++)
        {
            bufferArray[i] = bufferArray[i+1]; 
        }
        numRequests--;
    }
    free(frontVal);
} 
