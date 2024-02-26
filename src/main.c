#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

/* is_operator: checks if s is an operator; returns its ascii code, else 0 */
int is_operator(const char *s) {
	unsigned length = 0;

	while (*(s + length) != '\0') length++;
	if (length > 1) return 0;
	if (*s != '+' && *s != '-' && *s != 'x' && *s != '/') return 0;
	return (int)*s;
}

/* canstrtoi: checks if s can be converted to int; returns the length if so, else 0 */
unsigned canstrtoi(const char *s) {
	unsigned length = 0;

	while (*(s + length) != '\0') {
		char ch = *(s + length);

		if (ch == '-') {
			if (length == 0) {
				length++;
			} 
			else return 0;
		}
		else if (ch >= '0' && ch <= '9') {
			length++;
		}
		else return 0;
	}

	if ((char)*s == '-' && length == 1) return 0;

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

	Stack *s = new_stack(sizeof(int));

	if (s == NULL) return 1;

	for (int i = 1; i < argc; i++) {
		if (canstrtoi(argv[i]) == 0) {
			int op = is_operator(argv[i]);
			if (op == 0) return 1;

			int *result_value = pop_node(s)->value;
			while (s->length != 0) {
				int *curr_value = pop_node(s)->value;
				if (op == '+')
					*result_value = *curr_value + *result_value;
				else if (op == '-')
					*result_value = *curr_value - *result_value;
				else if (op == 'x')
					*result_value = *curr_value * *result_value;
				else if (op == '/') {
					if (*result_value == 0) {
						printf("Error: attempt to divide by 0.\n");
						return 1;
					}
					*result_value = *curr_value / *result_value;
				}

			}

			push_node(s, new_node(result_value));
		} else {
			int *v = malloc(sizeof(int));
			if (v == NULL) return 1;

			*v = strtoi(argv[i]);

			Node *n = new_node(v);
			if (n == NULL) return 1;

			push_node(s, n);

		}
	}

	int *result = pop_node(s)->value;
	printf("Result: %d\n", *result);

	return 0;
}
