#MAKEFILE VARIABLES
CC = clang
CFLAGS = -Wall -Werror -std=c11 -g -pthread -fsanitize=thread
LDFLAGS = -pthread -fsanitize=thread
OBJ = lift_sim_A.o fileManager.o queue.o lift.o
EXEC = lift_sim_A

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

#FILES IN MAKEFILES
lift_sim_A.o : lift_sim_A.c fileManager.h lift.h 
	$(CC) $(CFLAGS) lift_sim_A.c -c 

fileManager.o : fileManager.c fileManager.h lift.h queue.h
	$(CC) $(CFLAGS) fileManager.c -c 

queue.o : queue.c queue.h lift.h
	$(CC) $(CFLAGS) queue.c -c

lift.o : lift.c lift.h
	$(CC) $(CFLAGS) lift.c -c

clean: 
	rm -f $(EXEC) $(OBJ)