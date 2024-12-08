#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "die.h"

/* is_operator: checks if s is an operator; returns its ascii code, else 0 */
int is_operator(const char *s) {
	unsigned length = 0;

	while (*(s + length) != '\0') length++;
	if (length > 1) return 0;
	if (*s != '+' && *s != '-' && *s != 'x' && *s != '*' && *s != '/') return 0;
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

	Stack *stack = new_stack(sizeof(int));

	for (int i = 1; i < argc; i++) {
		if (canstrtoi(argv[i]) == 0) {
			int op = is_operator(argv[i]);
			if (op == 0) return 1;
            if (stack->length == 0) return 1;

            Node *value_a_node = pop_node(stack);
            if (!value_a_node)
                die(value_a_node, "last result node is NULL");

            while (stack->length != 0) {
                Node *value_b_node = pop_node(stack);
                if (!value_b_node)
                    die(value_b_node, "current result node is NULL");

                int *value_a = value_a_node->value;
                int *value_b = value_b_node->value;

                // Input order: value_n ... value_b value_a <operator>

                if (op == '+')
                    *value_a = *value_b + *value_a; 
                else if (op == '-')
                    *value_a = *value_b - *value_a; 
                else if (op == 'x' || op == '*')
                    *value_a = *value_b * *value_a; 
                else if (op == '/') {
                    if (*value_a == 0) {
                        printf("Error: attempt to divide by 0.\n");
                        return 1;
                    }
                    *value_a = *value_b / *value_a; 
                }

                free(value_b_node->value);
                free(value_b_node);
            }

            push_node(stack, value_a_node);
		} else {
            int *value_p = malloc(sizeof(int));
            *value_p = strtoi(argv[i]);
            Node *valueNode = new_node(value_p);
			push_node(stack, valueNode);
		}
	}

	Node *end_result = pop_node(stack);
    int *end_result_value = end_result->value;
	printf("Result: %d\n", *end_result_value);

    free(end_result->value);
    free(end_result);
    free(stack);

	return 0;
}
