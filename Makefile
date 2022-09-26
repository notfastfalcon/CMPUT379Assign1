CC = g++
CFLAGS = -Wall -O2

all: shell379

run: shell379
	./shell379

shell379: mainActivity.o commandHandler.o
	$(CC) mainActivity.o commandHandler.o -o shell379

mainActivity.o: mainActivity.cpp
	$(CC) -c mainActivity.cpp -o mainActivity.o

commandHandler.o: commandHandler.cpp
	$(CC) -c commandHandler.cpp -o commandHandler.o

clean: 
	rm -f mainActivity.o commandHandler.o shell379
