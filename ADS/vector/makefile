########## VECTOR MAKEFILE ##########

# we are using gcc,hence the need to define CC
CC=gcc

# included directory
INC_DIR=../include

# Object files directory
#     To put object files in current directory, use a dot (.), do NOT make
#     this an empty or blank macro!
OBJDIR = ../Lib

# C compiler flags
CFLAGS = -g -ansi -pedantic -Werror -Wall -fpic
CFLAGS+=-I$(INC_DIR)

export LD_LIBRARY_PATH := ../lib:$(LD_LIBRARY_PATH)

# Linker (ld) flags
LDFLAGS = -g -L../Lib -l GenDS

SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)

vpath %.h ../include

PRIMARY= generic_vector.o
TARGET=generic_vectorUT

ALL: $(TARGET) run

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

