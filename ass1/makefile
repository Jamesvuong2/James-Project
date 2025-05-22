CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJ = main.o game.o
EXEC = escape


ifdef CUBE
CFLAGS += -D CUBE
CUBE : clean $(EXEC)
endif


$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c game.h
	$(CC) $(CFLAGS) main.c -c

game.o : game.c game.h
	$(CC) $(CFLAGS) game.c -c

clean :
	rm -f $(EXEC) $(OBJ)