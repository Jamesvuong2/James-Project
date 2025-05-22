CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o calculate.o parity.o
EXEC = myProgram


ifdef CUBE
CFLAGS += -D CUBE
CUBE : clean $(EXEC)
endif


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c calculate.h parity.h
	$(CC) $(CFLAGS) main.c -c

calculate.o : calculate.c calculate.h
	$(CC) $(CFLAGS) calculate.c -c

parity.o : parity.c parity.h
	$(CC) $(CFLAGS) parity.c -c

clean :
	rm -f $(EXEC) $(OBJ)