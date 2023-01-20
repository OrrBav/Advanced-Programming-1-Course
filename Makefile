# Makefile for running two programs

# Chooses the right compiler.
CC = g++ -std=c++11
# Have the right clean command.
ifeq ($(OS),Windows_NT)
	CLN=del
else
	CLN=rm
endif

BUILD_FILES += distanceMatric.o
BUILD_FILES += helperFunctions.o
BUILD_FILES += knn.o
BUILD_FILES += CLI.o
BUILD_FILES += readFromFile.o


all: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES) server.o -o server.out -pthread
	$(CC) $(BUILD_FILES) client.o -o client.out -pthread

run: $(BUILD_FILES) server.o client.o
	$(CC) $(BUILD_FILES)  server.o -o server.out & $(CC) $(BUILD_FILES) client.o -o client.out

# Build the algs folder
%.o: %.cpp %.h
	$(CC) -c -o $@ $<

server.o: server.cpp
	$(CC) -c -o server.o server.cpp
client.o: client.cpp
	$(CC) -c -o client.o client.cpp

# Clean command
clean:
	$(CLN) *.o server.out client.out