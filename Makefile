# Makefile for Winman source and examples
# MIT License
# Julien LE THENO

all: setup test 

SHELL:=/bin/bash
MAKE=make

BUILD_DIR=build
OBJECTS_DIR=$(BUILD_DIR)/obj
EXE_DIR=$(BUILD_DIR)/exe
SRC_DIR=src
EXAMPLES_DIR=examples
TERMLIB_DIR=termlib
TERMLIB_OBJ_DIR=$(TERMLIB_DIR)/build/obj


F1_EXISTS=$(shell [ -e $(BUILD_DIR) ] && echo Y || echo N )

.PHONY: all test termlib clean

### EXAMPLES TARGETS

# TEST EXAMPLE
test: termlib test.o 
	gcc -o $(EXE_DIR)/test_exe $(TERMLIB_OBJ_DIR)/* $(OBJECTS_DIR)/* -lpthread -lm

test.o: winman.o tasks_mgmt.o $(EXAMPLES_DIR)/test.c $(SRC_DIR)/winman.h $(TERMLIB_DIR)/src/screen.h
	gcc -g -c $(EXAMPLES_DIR)/test.c $(SRC_DIR) -o  $(OBJECTS_DIR)/test.o
### END EXAMPLE TARGETS


### LIB TARGET

tasks_mgmt.o: $(SRC_DIR)/tasks_mgmt.c $(SRC_DIR)/tasks_mgmt.h 
	gcc -g -c $(SRC_DIR)/tasks_mgmt.c -o  $(OBJECTS_DIR)/tasks_mgmt.o

winman.o: $(SRC_DIR)/winman.c $(SRC_DIR)/winman.h 
	gcc -g -c $(SRC_DIR)/winman.c -o  $(OBJECTS_DIR)/winman.o

### END LIB TARGET

setup:
ifeq ($(F1_EXISTS),N)
	@echo "Creating build directory"
	mkdir $(BUILD_DIR)
	mkdir $(EXE_DIR)
	mkdir $(OBJECTS_DIR)
endif

termlib:
	cd $(TERMLIB_DIR) && $(MAKE) lib

make clean:
	rm -f $(EXE_DIR)/*
	rm -f $(OBJECTS_DIR)/*
	cd $(TERMLIB_DIR) && $(MAKE) clean

make rebuild: clean all
