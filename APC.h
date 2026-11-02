#ifndef APC_H

#define APC_H

#include <stdio.h>
#include <stdlib.h>

// Return values used by all APC functions.
#define SUCCESS 0
#define FAILURE -1

// Data type used to store each digit.
typedef int data_t;

// Node used for the doubly linked list.
// Each node stores one digit of the number.
typedef struct APC_Calculator
{
    data_t data;

    // Points to the previous digit.
    struct APC_Calculator *prev;

    // Points to the next digit.
    struct APC_Calculator *next;

} apc;


// Performs addition of two numbers.
int addition(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr);

// Performs subtraction of two numbers.
int subtraction(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr);

// Performs multiplication of two numbers.
int multiplication(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr);

// Performs division of two numbers.
int division(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr);

// Compares two numbers stored in linked lists.
int list_compare(apc *head1, apc *head2);

// Creates a linked list from the input number.
int createlist(apc **head, apc **tail, const char *number);

// Prints the number stored in the linked list.
void print_list(apc *head);

// Frees all nodes of the linked list.
void free_list(apc **head);

#endif