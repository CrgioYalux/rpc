#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"

signed strtoi(char *s) {
	signed result = 0;
	unsigned i = 0;
	unsigned length = 0;
	signed sign = 1;

	while (*(s + length) != '\0') length++;

	while (*(s + i) != '\0') {
		length--;

		char ch = *(s + i);

		if (i == 0 && ch == '-') sign = -1;
		if (ch < '0' || ch > '9') return 0;

		result = result + pow(10, length) * (ch - '0');

		i++;
	}

	return result * sign;
}

int main(int argc, char **argv) {
	if (argc == 1) return 0;

	int result = 0;

	Stack *s = new_stack(sizeof(int));

	if (s == NULL) return 1;

	for (int i = 1; i < argc; i++) {
		int *v = malloc(sizeof(int));

		if (v == NULL) return 1;

		*v = strtoi(argv[i]);
		Node *n = new_node(v);

		if (n == NULL) return 1;

		push_node(s, n);
	}

	print_int_node_stack(s);

	return 0;
}
