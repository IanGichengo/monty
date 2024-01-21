#include "main.h"

/**
 * push - Adds a new element to the stack
 * @stack: Pointer to the stack
 * @n: Integer to be added to the stack
 */
void push(stack_t **stack, int n)
{
    stack_t *new;

    new = malloc(sizeof(stack_t));
    if (new == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new->n = n;
    new->next = *stack;
    *stack = new;
}

/**
 * pall - Prints all elements of the stack
 * @stack: Pointer to the stack
 */
void pall(stack_t *stack)
{
    while (stack)
    {
        printf("%d\n", stack->n);
        stack = stack->next;
    }
}

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
    stack_t *stack = NULL;
    int i;

    for (i = 1; i < argc; i++)
    {
        push(&stack, atoi(argv[i]));
    }

    pall(stack);

    return (EXIT_SUCCESS);
}

