CC=gcc
FLAGS=-c -I include/
SRC=$(wildcard src/*.c)
OBJ=$(patsubst src/%.c, obj/%.o, $(SRC))
NAME=lab-02_cstrings

all: $(NAME)

obj/%.o: src/%.c include/%.h
	$(CC) $(FLAGS) $< -o $@


obj/main.o: src/main.c
	$(CC) $(FLAGS) src/main.c -o obj/main.o

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
clean:
	@rm -rf obj/*.o
	@rm -rf $(NAME)

.PHONY: clean
