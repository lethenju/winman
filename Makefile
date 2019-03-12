# Makefile for Winman source and examples
# MIT License
# Julien LE THENO

all: setup clean test 

SHELL:=/bin/bash
MAKE=make

BUILD_DIR=build
OBJECTS_DIR=$(BUILD_DIR)/obj
EXE_DIR=$(BUILD_DIR)/exe
SRC_DIR=src
EXAMPLES_DIR=examples
INC_DIR+=inc termlib/inc  termlib/log_system/inc
INC_PARAM=$(foreach d, $(INC_DIR), -I$d)
TERMLIB_DIR=termlib
TERMLIB_OBJ_DIR=$(TERMLIB_DIR)/build/obj/* $(TERMLIB_DIR)/log_system/build/obj


F1_EXISTS=$(shell [ -e $(BUILD_DIR) ] && echo Y || echo N )

.PHONY: all test termlib clean

### EXAMPLES TARGETS

# TEST EXAMPLE
test: clean termlib test.o 
	gcc -o $(EXE_DIR)/test_exe $(TERMLIB_OBJ_DIR)/* $(OBJECTS_DIR)/* -lpthread -lm

test.o: widgets.o winman.o tasks_mgmt.o $(EXAMPLES_DIR)/test.c 
	gcc -g -c $(EXAMPLES_DIR)/test.c $(SRC_DIR) $(INC_PARAM) -o  $(OBJECTS_DIR)/test.o
### END EXAMPLE TARGETS


### LIB TARGET

tasks_mgmt.o: $(SRC_DIR)/tasks_mgmt.c 
	gcc -g -c $(SRC_DIR)/tasks_mgmt.c $(INC_PARAM) -o $(OBJECTS_DIR)/tasks_mgmt.o

winman.o: $(SRC_DIR)/winman.c
	gcc -g -c $(SRC_DIR)/winman.c $(INC_PARAM) -o $(OBJECTS_DIR)/winman.o

widgets.o: $(SRC_DIR)/widgets.c
	gcc -g -c $(SRC_DIR)/widgets.c $(INC_PARAM) -o $(OBJECTS_DIR)/widgets.o

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


build_and_launch: all
	$(shell xfce4-terminal -e termlib/log_system/build/exe/server_exe)
	$(shell xfce4-terminal --geometry 100x50 -e build/exe/test_exe)