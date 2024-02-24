#include <stdio.h>
#include "node.h"

struct TStack {
	Node *head;
	size_t data_size;
	size_t length;
};

#define Stack struct TStack

Stack *new_stack(size_t data_size);

void push_node(Stack *stack, Node *node);

Node *pop_node(Stack *stack);

void pop_all(Stack *stack);

void print_node(void (*print)(void*), Node *node);

void print_int_node_value(void *value);

void print_int_node(Node *node);

void walk_stack(Node *head, void (*callback)(Node*));

void print_int_node_stack(Stack *stack);
