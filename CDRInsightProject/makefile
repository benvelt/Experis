########## CDR PROJECT MAKEFILE ##########

# we are using gcc,hence the need to define CC
CC=gcc

# included directory
ADS_DIR=./ads
ATTACH_DIR=./attach
INCLUDE_DIR=./include

# Object files directory
OBJ_DIR = ./obj/

# C compiler flags
CFLAGS= -g -ansi -pedantic -Werror -Wall -pthread -std=c99

CFLAGS += -I$(ADS_DIR)
CFLAGS += -I$(ATTACH_DIR)
CFLAGS += -I$(INCLUDE_DIR)

# Linker (ld) flags
LDFLAGS = -g -L./ads/Lib -l ADS -pthread

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

PRIMARY=manager.o
TARGET=MAIN

export LD_LIBRARY_PATH := ./ads/Lib:$(LD_LIBRARY_PATH)

ALL: $(TARGET) run

$(TARGET) : $(OBJECTS)
	$(CC)   $^   -o   $@   $(LDFLAGS)

clean: 
	rm $(OBJ_DIR)*.o
	rm $(TARGET)

run:
	mv *.o $(OBJ_DIR)
	mv ./done_CDR_files/*.cdr ./new_CDR_files
	./$(TARGET)

valgrind :
	valgrind ./$(TARGET)

.PHONY: ALL clean run valgrind
