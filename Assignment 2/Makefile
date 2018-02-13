OBJECTS = matrix.o test_matrix.o
EXEC_NAME = test_matrix
CC = g++
CFLAGS = -Wall -lm

all: matrix.o test_matrix.o
	$(CC) -o $(EXEC_NAME) matrix.o test_matrix.o $(CFLAGS)

matrix.o: matrix.cc matrix.h
	$(CC) -c matrix.cc $(CFLAGS)

test_matrix.o: test_matrix.cc matrix.h
	$(CC) -c test_matrix.cc $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

