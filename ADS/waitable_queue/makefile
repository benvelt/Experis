########## QUEUE MAKEFILE ##########

# we are using gcc,hence the need to define CC
CC=gcc

# included directory
INC_DIR=../include

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = ../Lib

# C compiler flags
CFLAGS = -g -ansi -pedantic -Werror -Wall -fpic -pthread
CFLAGS+=-I$(INC_DIR)

# Linker (ld) flags
LDFLAGS = -g -pthread -L../Lib -l GenDS

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

vpath %.h ../include

PRIMARY= generic_waitablequeue.o
TARGET=generic_queueUT

ALL: $(TARGET)

.PHONY: ALL clean run

.SILENT :

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
