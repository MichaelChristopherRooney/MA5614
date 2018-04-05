OBJECTS = main.o fish.o shark.o minnow.o tuna.o grid.o
EXEC_NAME = prog
CC = g++
CFLAGS = -Wall

all: main.o fish.o shark.o minnow.o tuna.o grid.o
	$(CC) -o $(EXEC_NAME) main.o fish.o shark.o $(CFLAGS)

main.o: main.cc fish.h
	$(CC) -c main.cc $(CFLAGS)

fish.o: fish.cc fish.h
	$(CC) -c fish.cc $(CFLAGS)

shark.o: shark.cc shark.h fish.h
	$(CC) -c shark.cc $(CFLAGS)

tuna.o: tuna.cc tuna.h fish.h
	$(CC) -c tuna.cc $(CFLAGS)

minnow.o: minnow.cc minnow.h fish.h
	$(CC) -c minnow.cc $(CFLAGS)

grid.o: grid.cc grid.h
	$(CC) -c grid.cc $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

