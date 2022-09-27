CC = g++
CFLAGS = -Wall -O2

all: shell379

run: shell379
	./shell379

shell379: mainActivity.o commandHandler.o utility.o
	$(CC) mainActivity.o commandHandler.o utility.o -o shell379

mainActivity.o: mainActivity.cpp
	$(CC) -c mainActivity.cpp -o mainActivity.o

commandHandler.o: commandHandler.cpp
	$(CC) -c commandHandler.cpp -o commandHandler.o

utility.o: utility.cpp
	$(CC) -c utility.cpp -o utility.o

clean: 
	rm -f mainActivity.o commandHandler.o utility.o shell379
