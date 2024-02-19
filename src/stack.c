#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *new_stack(size_t data_size) {
	Stack *head = malloc(sizeof(Stack));

	if (head == NULL) return NULL;

	head->data_size = data_size;
	head->head = NULL;

	// printf("Stack: in %p, size: %lu\n", head, sizeof(*head));

	return head;
}

void push_node(Stack *stack, Node *node) {
	if (stack->head == NULL) {
		node->next = NULL;
		stack->head = node;
	} else {
		node->prev = stack->head;
		node->next = NULL;
		stack->head = node;
	}

	stack->length = stack->length + 1;
}

Node *pop_node(Stack *stack) {
	Node *node = new_node(stack->head->value);
	
	if (stack->head == NULL) return NULL;

	if (stack->head->prev == NULL) {
		stack->head = NULL;
	} else {
		stack->head->prev->next = NULL;
		stack->head = stack->head->prev;
	}

	stack->length = stack->length - 1;

	return node;
}

/* Display stack */

void print_node(void (*print)(void*), Node *node) {
	printf("Node Position: %p\n", node);
	printf("Node Value: ");
	print(node->value);
	printf("\n\n");
}

void print_int_node_value(void *value) {
	printf("%d", *((int *)value));
}

void print_int_node(Node *node) {
	print_node(print_int_node_value, node);
}

void walk_stack(Node *head, void (*callback)(Node*)) {
	if (head == NULL) return;

	callback(head);

	walk_stack(head->prev, callback);
}

void print_int_node_stack(Stack *stack) {
	printf("Stack length: %lu\n", stack->length);
	walk_stack(stack->head, print_int_node);
}
