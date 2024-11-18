CC = gcc
CFLAGS = -Wall -g
LDFLAGS =
SRC_DIR = src
OBJ_DIR = obj
TARGET = nsh

SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/execute.c $(SRC_DIR)/builtins.c $(SRC_DIR)/utils.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(shell mkdir -p $(OBJ_DIR))

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

run:/$(TARGET)
	./$(TARGET)

.PHONY: all clean run