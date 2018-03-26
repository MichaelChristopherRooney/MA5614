OBJECTS = game.o board.o player.o
EXEC_NAME = game
CC = g++
CFLAGS = -Wall

all: game.o board.o player.o
	$(CC) -o $(EXEC_NAME) game.o board.o player.o $(CFLAGS)

player.o: player.cc player.h board.h
	$(CC) -c player.cc $(CFLAGS)

board.o: board.cc board.h
	$(CC) -c board.cc $(CFLAGS)

game.o: game.cc board.h
	$(CC) -c game.cc $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

