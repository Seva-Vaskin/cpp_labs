CC=gcc
FLAGS=-c -I include/ -Wall -Wextra -Werror
OBJ_DIR=obj
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRC))
NAME=lab-03_mergesort

all: $(NAME)

$(OBJ_DIR): 
	mkdir $@

obj/%.o: src/%.c include/%.h | $(OBJ_DIR)
	$(CC) $(FLAGS) $< -o $@


obj/main.o: src/main.c | $(OBJ_DIR)
	$(CC) $(FLAGS) $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
clean:
	rm -rf obj/
	rm -rf $(NAME)

.PHONY: clean
