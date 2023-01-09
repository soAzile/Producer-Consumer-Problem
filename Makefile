CC = g++
CFLAGS += -Wall -pthread

all: main

main:
	$(CC) main.cpp -o main $(CFLAGS)

clean:
	rm -f *.o main