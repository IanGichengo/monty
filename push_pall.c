#include "main.h"

/**
 * push - Pushes an element onto the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the file.
 */

void push(stack_t **stack, unsigned int line_number)
{
	char *n_str = strtok(NULL, " \n");
	int n;
	stack_t *new_node = malloc(sizeof(stack_t));

	if (!n_str || !is_numeric(n_str))
	{
		fprintf(stderr, "L%d: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}

	n = atoi(n_str);

	if (!new_node)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = n;
	new_node->next = *stack;
	new_node->prev = NULL;

	if (*stack)
		(*stack)->prev = new_node;

	*stack = new_node;
}

/**
 * pall - Prints all the values on the stack.
 * @stack: A pointer to the top of the stack.
 * @line_number: The line number in the file.
 */

void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;

	while (temp)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * is_numeric - Checks if a string is a numeric value.
 * @str: The string to check.
 * Return: 1 if numeric, 0 otherwise.
 */

int is_numeric(char *str)
{
	if (!str || *str == '\0')
		return (0);

	for (; *str; str++)
	{
		if (*str < '0' || *str > '9')
			return (0);
	}

	return (1);
}

int main(int argc, char *argv[])
{
	unsigned int line_number = 0;
	stack_t *stack = NULL;
	FILE *file = fopen(argv[1], "r");
	char *line = NULL;
	char *opcode = strtok(line, " \n");
	size_t len = 0;
	ssize_t read;
	(void)argc;

	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;

		if (opcode)
		{
			if (strcmp(opcode, "push") == 0)
				push(&stack, line_number);
			else if (strcmp(opcode, "pall") == 0)
				pall(&stack, line_number);
		}
	}
	fclose(file);
	free(line);
	while (stack)
	{
		stack_t *temp = stack;

		stack = stack->next;
		free(temp);
	}
	return (0);
}
