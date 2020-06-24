#MAKEFILE VARIABLES
CC = clang
CFLAGS = -Wall -Werror -std=gnu99 -g -pthread -fsanitize=thread
LDFLAGS = -pthread -fsanitize=thread  
OBJ = lift_sim_B.o fileManager.o queue.o lift.o processes.o
EXEC = lift_sim_B

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

#FILES IN MAKEFILES
lift_sim_B.o : lift_sim_B.c fileManager.h lift.h 
	$(CC) $(CFLAGS) lift_sim_B.c -c 

fileManager.o : fileManager.c fileManager.h lift.h queue.h
	$(CC) $(CFLAGS) fileManager.c -c 

queue.o : queue.c queue.h lift.h
	$(CC) $(CFLAGS) queue.c -c

lift.o : lift.c lift.h
	$(CC) $(CFLAGS) lift.c -c

processes.o : processes.c processes.h fileManager.h
	$(CC) $(CFLAGS) processes.c -c

clean: 
	rm -f $(EXEC) $(OBJ)