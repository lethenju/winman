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
INC_DIR+=inc termlib/inc  termlib/log_system/inc termlib/resman/inc
INC_PARAM=$(foreach d, $(INC_DIR), -I$d)
TERMLIB_DIR=termlib
TERMLIB_OBJ_DIR=$(TERMLIB_DIR)/build/obj/* $(TERMLIB_DIR)/log_system/build/obj/* $(TERMLIB_DIR)/resman/build/obj


F1_EXISTS=$(shell [ -e $(BUILD_DIR) ] && echo Y || echo N )

.PHONY: all test termlib clean

### EXAMPLES TARGETS

# TEST EXAMPLE
test: clean termlib test.o 
	@echo -e "\e[34m"
	gcc -o $(EXE_DIR)/test_exe $(TERMLIB_OBJ_DIR)/* $(OBJECTS_DIR)/* -lpthread -lm
	@echo -e "\e[39m"

test.o: widgets.o winman.o tasks_mgmt.o $(EXAMPLES_DIR)/test.c 
	@echo -e "\e[34m"
	gcc -g -c $(EXAMPLES_DIR)/test.c $(SRC_DIR) $(INC_PARAM) -o  $(OBJECTS_DIR)/test.o
	@echo -e "\e[39m"

### END EXAMPLE TARGETS


### LIB TARGET

tasks_mgmt.o: $(SRC_DIR)/tasks_mgmt.c 
	@echo -e "\e[92m"
	gcc -g -c $(SRC_DIR)/tasks_mgmt.c $(INC_PARAM) -o $(OBJECTS_DIR)/tasks_mgmt.o
	@echo -e "\e[39m"


winman.o: $(SRC_DIR)/winman.c
	@echo -e "\e[92m"
	gcc -g -c $(SRC_DIR)/winman.c $(INC_PARAM) -o $(OBJECTS_DIR)/winman.o
	@echo -e "\e[39m"

widgets.o: $(SRC_DIR)/widgets.c
	@echo -e "\e[92m"
	gcc -g -c $(SRC_DIR)/widgets.c $(INC_PARAM) -o $(OBJECTS_DIR)/widgets.o
	@echo -e "\e[39m"

### END LIB TARGET

setup:
ifeq ($(F1_EXISTS),N)
	@echo -e " \e[33mCreating build directory"
	mkdir $(BUILD_DIR)
	mkdir $(EXE_DIR)
	mkdir $(OBJECTS_DIR)
	@echo -e "done.. \e[39m"
endif

termlib:
	@echo -e "\e[32mBuilding termlib and its dependencies :"
	cd $(TERMLIB_DIR) && $(MAKE) lib
	@echo -e "\e[39m"

make clean:
	@echo -e "\e[96mCleaning"
	rm -f $(EXE_DIR)/*
	rm -f $(OBJECTS_DIR)/*
	cd $(TERMLIB_DIR) && $(MAKE) clean
	@echo -e "Cleaning done !\e[39m"

make rebuild: clean all


build_and_launch: all
	$(shell xfce4-terminal -e termlib/log_system/build/exe/server_exe)
	$(shell xfce4-terminal --geometry 100x50 -e build/exe/test_exe)