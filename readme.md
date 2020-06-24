# Operating Systems Assignment Readme

Date last modified: 09/05/2020

## Purpose: 
- To simulate 3 consumer lifts receiving requests from a producer lift_R (Procuder/Consumer Problem) in 2 different ways, threads and processes.

## Functionality: 
To compile: `make clean` and then `make`

Threads: `./lift_sim_A <buffer size> <sleep time>`
Processes: `./lift_sim_B <buffer size> <sleep time>`
Make sure buffer size is greater than 1 and sleep time is not a negative number (0 is allowed

To run with valgrind make sure the fsantize flag in the Makefile is commented out/removed

**NOTE**: This program will not work on MAC OSX because sem_init and sem_destroy are being used and they aren't available on MAC OSX
