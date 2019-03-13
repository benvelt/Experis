CC=g++

# C++ compiler flags
CXXFLAGS:= -g -pedantic -ansi -Wall -Werror -std=c++03 -pthread -ldl -fpic -I./inc -I./inc/devices -I./inc/mediator -I./inc/configuration -I./inc/threads

# Target and sources
TARGET=main

SRC_FOLDER=./src
OBJ_FOLDER= $(SRC_FOLDER)/obj
DEVICES_FOLDER= $(SRC_FOLDER)/devices
LIB=./src/lib

SOURCES:= $(wildcard $(SRC_FOLDER)/*.cpp) $(wildcard *.cpp)
OBJECTS:= $(SOURCES:.cpp=.o)

ALL : $(TARGET) $(devices) $(libs) $(run)

$(TARGET) : $(OBJECTS)
	$(CC) $^  $(CXXFLAGS)  -o $(TARGET)
	mv $(SRC_FOLDER)/*.o $(OBJ_FOLDER)

libs : $(LIB)/fireCtrl.so $(LIB)/waterCtrl.so $(LIB)/fireSensor.so $(LIB)/waterSensor.so

$(LIB)/fireCtrl.so : $(OBJ_FOLDER)/fireCtrl.o $(OBJ_FOLDER)/icontroller.o $(OBJ_FOLDER)/event.o $(OBJ_FOLDER)/idevice.o
		$(CC) -fpic -shared $^ -o $@

$(LIB)/waterCtrl.so : $(OBJ_FOLDER)/waterCtrl.o $(OBJ_FOLDER)/icontroller.o $(OBJ_FOLDER)/event.o $(OBJ_FOLDER)/idevice.o
		$(CC) -fpic -shared $^ -o $@

$(LIB)/fireSensor.so : $(OBJ_FOLDER)/fireSensor.o $(OBJ_FOLDER)/idevice.o $(OBJ_FOLDER)/event.o $(OBJ_FOLDER)/runnable.o $(OBJ_FOLDER)/thread.o
		$(CC) -fpic -shared $^ -o $@

$(LIB)/waterSensor.so : $(OBJ_FOLDER)/waterSensor.o $(OBJ_FOLDER)/idevice.o $(OBJ_FOLDER)/event.o $(OBJ_FOLDER)/runnable.o $(OBJ_FOLDER)/thread.o
		$(CC) -fpic -shared $^ -o $@

devices :
	mv $(DEVICES_FOLDER)/fireCtrl.cpp $(SRC_FOLDER)
	$(MAKE)
	mv $(SRC_FOLDER)/fireCtrl.cpp $(DEVICES_FOLDER)
	mv $(DEVICES_FOLDER)/fireSensor.cpp $(SRC_FOLDER)
	$(MAKE)
	mv $(SRC_FOLDER)/fireSensor.cpp $(DEVICES_FOLDER)
	mv $(DEVICES_FOLDER)/waterCtrl.cpp $(SRC_FOLDER)
	$(MAKE)
	mv $(SRC_FOLDER)/waterCtrl.cpp $(DEVICES_FOLDER)
	mv $(DEVICES_FOLDER)/waterSensor.cpp $(SRC_FOLDER)
	$(MAKE)
	mv $(SRC_FOLDER)/waterSensor.cpp $(DEVICES_FOLDER)


clean :
	rm $(LIB)/*.so
	rm $(OBJ_FOLDER)/*.o
	rm $(TARGET).o
	rm $(TARGET)


run :
	./$(TARGET)

launch :
	$(MAKE)
	make devices
	make libs
	make run

