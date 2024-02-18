#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(void) {
	Stack *s = new_stack(sizeof(int));

	if (s == NULL) { 
		free(s);
		return 1;
	}

	int i = 5;
	Node *n1 = new_node(&i);

	if (n1 == NULL) {
		free(n1);
		return 1;
	}

	int j = 10;
	Node *n2 = new_node(&j);

	if (n2 == NULL) {
		free(n2);
		return 1;
	}

	int k = 15;
	Node *n3 = new_node(&k);

	if (n3 == NULL) {
		free(n3);
		return 1;
	}

	push_node(s, n1); 
	push_node(s, n2); 
	push_node(s, n3); 

	print_int_node_stack(s);

	pop_node(s);

	print_int_node_stack(s);

	free(n1);
	free(n2);
	free(s);

	return 0;
}
