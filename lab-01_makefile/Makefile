CC=gcc
FLAGS=-c -I include/
OBJ=obj/main.o obj/io.o obj/util.o obj/algorithm.o

all: lab-01_makefile

obj/main.o: src/main.c 
	$(CC) $(FLAGS) src/main.c -o obj/main.o

obj/io.o: src/io.c 
	$(CC) $(FLAGS) src/io.c -o obj/io.o

obj/util.o: src/util.c 
	$(CC) $(FLAGS) src/util.c -o obj/util.o

obj/algorithm.o: src/algorithm.c 
	$(CC) $(FLAGS) src/algorithm.c -o obj/algorithm.o

lab-01_makefile: $(OBJ)
	$(CC) $(OBJ) -o lab-01_makefile

clean:
	@rm -rf obj/*.o

.PHONY: clean