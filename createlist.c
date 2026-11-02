#include "APC.h"

// Creates a doubly linked list from the given number.
// Each digit is stored in a separate node.
int createlist(apc **head, apc **tail, const char *number)
{
    int i = 0;

    // Skip the sign if the number starts with '+' or '-'.
    if (number[0] == '-' || number[0] == '+')
    {
        i = 1;
    }

    // Read the number character by character.
    while (number[i] != '\0')
    {
        // Check whether the current character is a digit.
        if (number[i] >= '0' && number[i] <= '9')
        {
            // Create a new node for the digit.
            apc *new = malloc(sizeof(apc));

            // Stop if memory allocation fails.
            if (new == NULL)
            {
                return FAILURE;
            }

            // Convert the character digit into an integer.
            // Example: '7' - '0' gives 7.
            new->data = number[i] - '0';

            // New node is added at the end, so next is NULL.
            new->next = NULL;

            // Previous node becomes the previous link.
            new->prev = *tail;

            // If the list already has nodes, connect the old tail to new node.
            if (*tail != NULL)
            {
                (*tail)->next = new;
            }
            else
            {
                // If this is the first node, it becomes the head.
                *head = new;
            }

            // New node becomes the tail of the list.
            *tail = new;
        }
        else
        {
            // Reject the input if any non-digit character is found.
            printf("Invalid Character in number.\n");
            return FAILURE;
        }

        // Move to the next character in the input number.
        i++;
    }

    return SUCCESS;
}

// Compares two linked lists representing positive numbers.
// Returns 1 if first number is greater,
// -1 if second number is greater,
// 0 if both numbers are equal.
int list_compare(apc *head1, apc *head2)
{
    int len1 = 0;
    int len2 = 0;

    apc *temp1 = head1;
    apc *temp2 = head2;

    // Count the number of digits in the first list.
    while (temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }

    // Count the number of digits in the second list.
    while (temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    // A number with more digits is greater.
    if (len1 > len2)
    {
        return 1;
    }

    if (len1 < len2)
    {
        return -1;
    }

    // If both have the same number of digits,
    // compare them digit by digit from the head.
    temp1 = head1;
    temp2 = head2;

    while (temp1 != NULL && temp2 != NULL)
    {
        // First different digit decides which number is greater.
        if (temp1->data > temp2->data)
        {
            return 1;
        }

        if (temp1->data < temp2->data)
        {
            return -1;
        }

        // Move to the next digit in both lists.
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    // All digits are equal.
    return 0;
}

// Prints the complete number stored in the linked list.
void print_list(apc *head)
{
    // Check whether the list is empty.
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }

    // Print each digit from head to tail.
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

// Frees all nodes of the linked list.
void free_list(apc **head)
{
    apc *temp = *head;

    // Go through the list and free each node.
    while (temp != NULL)
    {
        // Move head to the next node before freeing current node.
        *head = temp->next;

        // Release the current node's memory.
        free(temp);

        // Continue with the next node.
        temp = *head;
    }
}