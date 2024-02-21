objects = main.o stack.o node.o
flags = -Wall -Wextra -pedantic -std=c99 -lm
CC = gcc

rpc: init $(objects)
	$(CC) -o build/rpc $(objects) $(flags)
	mv *.o build/
main.o: src/main.c src/stack.h
	$(CC) -o main.o -c src/main.c
stack.o: src/stack.c src/node.h
	$(CC) -o stack.o -c src/stack.c
node.o: src/node.c
	$(CC) -o node.o -c src/node.c
init:
	mkdir build/

.PHONY: clean rebuild
clean:
	rm -r build/
rebuild:
	rm -r build/
	make
