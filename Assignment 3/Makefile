OBJECTS = game.o board.o
EXEC_NAME = game
CC = g++
CFLAGS = -Wall

all: game.o board.o
	$(CC) -o $(EXEC_NAME) game.o board.o $(CFLAGS)

board.o: board.cc board.h
	$(CC) -c board.cc $(CFLAGS)

game.o: game.cc board.h
	$(CC) -c game.cc $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

