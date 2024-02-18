objects = main.o stack.o node.o
flags = -Wall -Wextra -pedantic

rpc: init $(objects)
	$(CC) $(flags) -o build/rpc $(objects)
	mv *.o build/
main.o: src/main.c src/stack.h
	$(CC) -c src/main.c -o main.o
stack.o: src/stack.c src/node.h
	$(CC) -c src/stack.c -o stack.o
node.o: src/node.c
	$(CC) -c src/node.c -o node.o
init:
	mkdir build/

.PHONY: clean
clean:
	rm -r rpc build/
