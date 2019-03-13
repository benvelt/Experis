########## STACK MAKEFILE ##########

# we are using gcc,hence the need to define CC
CC=gcc

# included directory
INC_DIR=../include

# Object files directory
OBJDIR = ../Lib

# C compiler flags
CFLAGS = -g -ansi -pedantic -Werror -Wall -fpic
CFLAGS+=-I$(INC_DIR)

# Linker (ld) flags
LDFLAGS = -g -L../Lib -l GenDS

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

vpath %.h ../include

PRIMARY=generic_stack.o
TARGET=generic_stackUT

export LD_LIBRARY_PATH := ../Lib:$(LD_LIBRARY_PATH)

ALL: $(TARGET) run

.PHONY: ALL clean run valgrind

$(TARGET) : $(OBJECTS)
	$(CC)   $^   -o   $@   $(LDFLAGS) 

clean: 
	rm *.o
	rm $(TARGET)

run:
	./$(TARGET)

commit :
	cp $(PRIMARY) $(OBJDIR)

valgrind :
	valgrind ./$(TARGET)

#.SILENT :
