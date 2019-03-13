########## ADS MAKEFILE ##########

# we are using gcc,hence the need to define CC
CC=gcc

# Object files directory
OBJDIR = ./obj/
LIBDIR = ./Lib/

# C compiler flags
CFLAGS = -g -ansi -pedantic -Werror -Wall -fpic -pthread

# Linker (ld) flags
LDFLAGS = -g

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

export LD_LIBRARY_PATH := ./Lib:$(LD_LIBRARY_PATH)

ALL: generic_waitablequeue.o generic_doubleLL.o Protected_Hash.o

generic_waitablequeue.o: generic_waitablequeue.c generic_queue.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)$@

generic_doubleLL.o: generic_doubleLL.c generic_doubleLL.h generic_doubleLL_itr.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)$@

Protected_Hash.o: Protected_Hash.c generic_doubleLL.c generic_doubleLL.h generic_doubleLL_itr.h Protected_Hash.h
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)$@

sharedlib :
	gcc $^ -shared -o $(LIBDIR)libADS.so $(OBJDIR)generic_waitablequeue.o $(OBJDIR)generic_doubleLL.o $(OBJDIR)Protected_Hash.o

clean: 
	rm $(OBJDIR)*.o

.PHONY: ALL clean

