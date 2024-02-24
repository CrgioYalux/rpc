#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

/* canstrtoi: checks if s can be converted to int; returns the length if so, else 0 */
unsigned canstrtoi(const char *s) {
	unsigned length = 0;

	while (*(s + length) != '\0') {
		char ch = *(s + length);
		if (ch < '0' || ch > '9') return 0;
		length++;
	}

	return length;
}

/* strtoi: converts s to an signed int; if there's no possible conversion, returns 0 */
signed strtoi(const char *s) {
	signed result = 0;
	unsigned i = 0;
	signed sign = 1;

	unsigned length = canstrtoi(s);
	if (length == 0) return 0;

	while (*(s + i) != '\0') {
		length--;

		char ch = *(s + i);

		if (i == 0 && ch == '-') {
			sign = -1;
			i = 1;
			continue;
		}

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
		if (canstrtoi(argv[i]) == 0) {
			printf("may entered an operand\n");
			// 1. check if operator
			// 2. if so, do the operation the operaton says with the nodes til then
			// 3. pop_all
			// 4. push the result from the operation as node
		} else {
			// it's an operand
			*v = strtoi(argv[i]);
			Node *n = new_node(v);
			if (n == NULL) return 1;
			push_node(s, n);
		}
	}

	print_int_node_stack(s);

	pop_all(s);

	print_int_node_stack(s);

	return 0;
}
