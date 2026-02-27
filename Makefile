# Variables
CC = gcc
CFLAGS = -Wall -I./include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

SOURCES = $(SRC_DIR)/talloc.c $(SRC_DIR)/tfree.c $(SRC_DIR)/tools.c $(SRC_DIR)/turboalloc.c main.c
OBJECTS = $(OBJ_DIR)/talloc.o $(OBJ_DIR)/tfree.o $(OBJ_DIR)/tools.o $(OBJ_DIR)/turboalloc.o $(OBJ_DIR)/main.o
EXECUTABLE = out

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(BIN_DIR)/$@

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)/$(EXECUTABLE)