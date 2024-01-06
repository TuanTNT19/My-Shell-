
CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
LIB_DIR := $(CUR_DIR)/lib
OBJ_DIR := $(CUR_DIR)/obj
SRC_DIR := $(CUR_DIR)/src
INC_DIR := $(CUR_DIR)/inc
INC_FLAG := -I $(INC_DIR)
CC := gcc
FLAG := -lreadline

mk_obj:
	$(CC) -c $(CUR_DIR)/main.c -o $(OBJ_DIR)/main.o 

all:    mk_obj
	$(CC) $(OBJ_DIR)/main.o -o $(BIN_DIR)/runfile $(FLAG)

run:
	./bin/runfile
clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(BIN_DIR)/*


