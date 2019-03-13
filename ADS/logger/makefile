########## LOGGER MAKEFILE ##########

# we are using gcc,hence the need to define CC
CC=gcc

# C compiler flags
CFLAGS = -g -pedantic -Werror -Wall -fpic
CFLAGS +=-DDEBUG

# Linker (ld) flags
LDFLAGS = -g

PRIMARY =zlog4c.o
TARGET =main

SOURCES =$(wildcard *.c)
OBJECTS =$(SOURCES:.c=.o)

#DEBUG ?= 0
#ifeq ($(DEBUG), 1)
#	CFLAGS +=-DDEBUG
#endif

.PHONY: all clean run commit valgrind .SILENT

all: $(TARGET) ./$(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC)   $^   -o   $@   $(LDFLAGS)

clean: 
	rm *.o
	rm $(TARGET)

staticlib :
	ar cvr ./Lib/libLOG.a $(OBJECTS)

sharedlib :
	gcc $^ -shared -o ./Lib/libLOG.so $(OBJECTS) 

valgrind :
	valgrind ./$(TARGET)

.SILENT :
