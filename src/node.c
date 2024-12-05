#include "node.h"
#include "die.h"
#include <stdlib.h>

Node *new_node(void *value) {
    if (!value)
        die(value, "value is NULL");

	Node *node = malloc(sizeof(Node));

    if (!node)
        die(node, "node is NULL");

	node->value = value;
	node->next = NULL;
	node->prev = NULL;

	return node;
}
