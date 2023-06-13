CC=g++
CFLAGS=-c -Wall -std=c++11 -O2 -fopenmp

# exec: sequential.o
# 	$(CC) sequential.o -fopenmp -o exec

# sequential.o: sequential.cpp
# 	$(CC) $(CFLAGS) sequential.cpp 

all:
	$(CC) $(CFLAGS) -fopenmp -o exec sequential.cpp

run:
	./exec 3

clean:
	rm -rf *.o exec


