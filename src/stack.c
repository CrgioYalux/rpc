#include "stack.h"
#include "die.h"
#include <stdio.h>
#include <stdlib.h>


Stack *new_stack(size_t data_size) {
	Stack *head = malloc(sizeof(Stack));

    if (!head)
        die(head, "head is NULL");

	head->data_size = data_size; // this does nothing btw; lazy past me
                                 // not gonna fix it; lazy current me
	head->length = 0;
	head->head = NULL;

	return head;
}

void push_node(Stack *stack, Node *node) {
    if (!stack) 
        die(stack, "stack is NULL");

    if (!node) 
        die(node, "node is NULL");

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
    if (!stack)
        die(stack, "stack is NULL");

	Node *node = new_node(stack->head->value);

    if (!node) 
        die(node, "node is NULL");

    if (!stack->head) 
        die(stack->head, "stack->head is NULL");

	if (stack->head->prev == NULL) {
        free(stack->head);
		stack->head = NULL;
	} else {
        Node *temp = stack->head;

		stack->head->prev->next = NULL;
		stack->head = stack->head->prev;

        free(temp);
	}

	stack->length = stack->length - 1;

	return node;
}

void pop_all(Stack *stack) {
	while (stack->length != 0) {
		pop_node(stack);
	}
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
