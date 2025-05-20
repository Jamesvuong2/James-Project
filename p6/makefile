CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = struct.o
EXEC = program

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

struct.o : struct.c struct.h
	$(CC) $(CFLAGS) struct.c -c

clean :
	rm $(OBJ) $(EXEC)