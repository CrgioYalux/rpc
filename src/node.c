#include <stdlib.h>
#include "node.h"

Node *new_node(void *value) {
	Node *node = malloc(sizeof(Node));

	if (node == NULL) return NULL;

	node->value = value;
	node->next = NULL;
	node->prev = NULL;

	return node;
}
