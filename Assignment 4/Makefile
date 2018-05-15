OBJECTS = main.o fishes.o grid.o point.o
EXEC_NAME = prog
CC = g++
CFLAGS = -Wall -Wextra -g

all: main.o fishes.o grid.o point.o
	$(CC) -o $(EXEC_NAME) main.o fishes.o grid.o point.o $(CFLAGS)

main.o: main.cc fishes.h grid.h point.h
	$(CC) -c main.cc $(CFLAGS)

fishes.o: fishes.cc fishes.h grid.h point.h
	$(CC) -c fishes.cc $(CFLAGS)


grid.o: grid.cc fishes.h grid.h point.h
	$(CC) -c grid.cc $(CFLAGS)

point.o: point.cc fishes.h grid.h point.h
	$(CC) -c point.cc $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

