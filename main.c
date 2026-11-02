// Author      : Kancharla Giri Babu
// Date        : 08-09-2026
// Description : Main file of the APC (Arbitrary Precision Calculator) project.

                // This file contains the main function of the APC calculator.
                // The program accepts two large numbers and an arithmetic
                // operator through command-line arguments.

                // The input values are validated before performing the
                // requested operation. Based on the operator provided,
                // the program performs arithmetic operations such as
                // addition, subtraction, multiplication, or division.

                // The numbers are stored and processed using doubly linked
                // lists so that the program can handle numbers larger than
                // the range supported by standard C data types.

                // The final result of the arithmetic operation is stored
                // and displayed to the user.

#include "APC.h"

int main(int argc, char *argv[])
{
    // Check command line arguments.
    // We need two numbers and one operator.
    if (argc != 4)
    {
        printf("Usage: ./apc <operand1> <operator> <operand2>\n");
        return FAILURE;
    }

    // Get the operator entered by the user.
    char operator = argv[2][0];

    // Store the sign of both numbers.
    // 1 means positive and -1 means negative.
    int sign1 = 1, sign2 = 1;

    // Check the sign of first number.
    if (argv[1][0] == '-')
        sign1 = -1;

    // Check the sign of second number.
    if (argv[3][0] == '-')
        sign2 = -1;

    // Select the operation according to the operator.
    switch (operator)
    {
    // Addition operation.
    case '+':
    {
        // Pointers for first number, second number and result list.
        apc *head1 = NULL, *tail1 = NULL;
        apc *head2 = NULL, *tail2 = NULL;
        apc *headr = NULL, *tailr = NULL;

        // Convert first number into a linked list.
        if (createlist(&head1, &tail1, argv[1]) == FAILURE)
        {
            printf("Failed to create First List\n");
            return FAILURE;
        }

        // Convert second number into a linked list.
        if (createlist(&head2, &tail2, argv[3]) == FAILURE)
        {
            printf("Failed to create Second List\n");
            free_list(&head1);
            return FAILURE;
        }

        // Compare both numbers.
        // This is useful when the signs are different.
        int compare = list_compare(head1, head2);

        // Positive number + positive number.
        if (sign1 == 1 && sign2 == 1)
        {
            // Add both linked lists.
            if (addition(&head1, &tail1,
                         &head2, &tail2,
                         &headr, &tailr) == FAILURE)
            {
                printf("Addition Failed\n");
                free_list(&head1);
                free_list(&head2);
                return FAILURE;
            }

            printf("operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("operand 2 : %s\n", argv[3]);
            printf("output : ");

            // Display the result list.
            print_list(headr);
        }

        // Positive number + negative number.
        // This becomes subtraction of their magnitudes.
        else if (sign1 == 1 && sign2 == -1)
        {
            // If first number is greater, subtract second from first.
            if (compare >= 0)
            {
                subtraction(&head1, &tail1,
                            &head2, &tail2,
                            &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("output : ");

                print_list(headr);
            }
            else
            {
                // If second number is greater, subtract first from second.
                // The result will be negative.
                subtraction(&head2, &tail2,
                            &head1, &tail1,
                            &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("Output : -");

                print_list(headr);
            }
        }

        // Negative number + negative number.
        // Add the magnitudes and print '-' before the result.
        else if (sign1 == -1 && sign2 == -1)
        {
            if (addition(&head1, &tail1,
                         &head2, &tail2,
                         &headr, &tailr) == FAILURE)
            {
                printf("Addition Failed\n");
                free_list(&head1);
                free_list(&head2);
                return FAILURE;
            }

            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : -");

            print_list(headr);
        }

        // Negative number + positive number.
        else if (sign1 == -1 && sign2 == 1)
        {
            // Compare magnitudes to decide which number is larger.
            if (compare >= 0)
            {
                subtraction(&head1, &tail1,
                            &head2, &tail2,
                            &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("Output : -");

                print_list(headr);
            }
            else
            {
                subtraction(&head2, &tail2,
                            &head1, &tail1,
                            &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("Output : ");

                print_list(headr);
            }
        }

        // Free all dynamically allocated lists.
        free_list(&head1);
        free_list(&head2);
        free_list(&headr);

        break;
    }

    // Subtraction operation.
    case '-':
    {
        // Pointers for both operands and the result.
        apc *head1 = NULL, *tail1 = NULL;
        apc *head2 = NULL, *tail2 = NULL;
        apc *headr = NULL, *tailr = NULL;

        // Convert first number into linked list.
        if (createlist(&head1, &tail1, argv[1]) == FAILURE)
        {
            printf("Failed to create First List\n");
            return FAILURE;
        }

        // Convert second number into linked list.
        if (createlist(&head2, &tail2, argv[3]) == FAILURE)
        {
            printf("Failed to create Second List\n");
            free_list(&head1);
            return FAILURE;
        }

        // Compare magnitudes of both numbers.
        int compare = list_compare(head1, head2);

        // Positive - positive.
        if (sign1 == 1 && sign2 == 1)
        {
            // If first number is greater or equal, result is positive.
            if (compare >= 0)
            {
                subtraction(&head1, &tail1, &head2, &tail2, &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("Output : ");

                print_list(headr);

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                break;
            }
            else
            {
                // If second number is greater, result becomes negative.
                subtraction(&head2, &tail2, &head1, &tail1, &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("Output : -");

                print_list(headr);

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                break;
            }
        }

        // Positive - negative becomes addition.
        else if (sign1 == 1 && sign2 == -1)
        {
            if (addition(&head1, &tail1, &head2, &tail2, &headr, &tailr) == FAILURE)
            {
                printf("Addition Failed\n");
                free_list(&head1);
                free_list(&head2);
                return FAILURE;
            }

            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : ");

            print_list(headr);

            free_list(&head1);
            free_list(&head2);
            free_list(&headr);

            break;
        }

        // Negative - negative.
        // The order of subtraction is reversed.
        else if (sign1 == -1 && sign2 == -1)
        {
            if (subtraction(&head2, &tail2, &head1, &tail1, &headr, &tailr) == FAILURE)
            {
                printf("Subtraction Failed\n");

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                return FAILURE;
            }

            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : ");

            print_list(headr);

            free_list(&head1);
            free_list(&head2);
            free_list(&headr);

            break;
        }

        // Negative - positive becomes negative addition.
        else if (sign1 == -1 && sign2 == 1)
        {
            if (addition(&head1, &tail1, &head2, &tail2, &headr, &tailr) == FAILURE)
            {
                printf("Subtraction Failed\n");

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                return FAILURE;
            }

            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : -");

            print_list(headr);

            free_list(&head1);
            free_list(&head2);
            free_list(&headr);

            break;
        }
    }

    // Multiplication operation.
    case 'x':
    case '*':
    {
        // Pointers for operands and result.
        apc *head1 = NULL, *tail1 = NULL;
        apc *head2 = NULL, *tail2 = NULL;
        apc *headr = NULL, *tailr = NULL;

        // Convert first number into linked list.
        if (createlist(&head1, &tail1, argv[1]) == FAILURE)
        {
            printf("Failed to create First List\n");
            return FAILURE;
        }

        // Convert second number into linked list.
        if (createlist(&head2, &tail2, argv[3]) == FAILURE)
        {
            printf("Failed to create Second List\n");
            free_list(&head1);
            return FAILURE;
        }

        // If any one number is zero, multiplication result is zero.
        if ((head1->data == 0 && head1 == tail1) ||
            (head2->data == 0 && head2 == tail2))
        {
            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : 0\n");

            free_list(&head1);
            free_list(&head2);

            break;
        }

        // Compare the two numbers.
        int compare = list_compare(head1, head2);

        // Positive * positive gives positive result.
        if (sign1 == 1 && sign2 == 1)
        {
            if (compare >= 0)
            {
                multiplication(&head1, &tail1, &head2, &tail2, &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("Output : ");

                print_list(headr);

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                break;
            }
            else
            {
                multiplication(&head2, &tail2, &head1, &tail1, &headr, &tailr);

                printf("Operand 1 : %s\n", argv[1]);
                printf("Operator : %s\n", argv[2]);
                printf("Operand 2 : %s\n", argv[3]);
                printf("Output : ");

                print_list(headr);

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                break;
            }
        }

        // Positive * negative gives negative result.
        else if (sign1 == 1 && sign2 == -1)
        {
            if (multiplication(&head1, &tail1, &head2, &tail2, &headr, &tailr) == FAILURE)
            {
                printf("Addition Failed\n");

                free_list(&head1);
                free_list(&head2);

                return FAILURE;
            }

            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : -");

            print_list(headr);

            free_list(&head1);
            free_list(&head2);
            free_list(&headr);

            break;
        }

        // Negative * negative gives positive result.
        else if (sign1 == -1 && sign2 == -1)
        {
            if (multiplication(&head2, &tail2, &head1, &tail1, &headr, &tailr) == FAILURE)
            {
                printf("Subtraction Failed\n");

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                return FAILURE;
            }

            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : ");

            print_list(headr);

            free_list(&head1);
            free_list(&head2);
            free_list(&headr);

            break;
        }

        // Negative * positive gives negative result.
        else if (sign1 == -1 && sign2 == 1)
        {
            if (multiplication(&head1, &tail1, &head2, &tail2, &headr, &tailr) == FAILURE)
            {
                printf("Subtraction Failed\n");

                free_list(&head1);
                free_list(&head2);
                free_list(&headr);

                return FAILURE;
            }

            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : -");

            print_list(headr);

            free_list(&head1);
            free_list(&head2);
            free_list(&headr);

            break;
        }
    }

    // Division operation.
    case '/':
    {
        // Pointers for operands and result.
        apc *head1 = NULL, *tail1 = NULL;
        apc *head2 = NULL, *tail2 = NULL;
        apc *headr = NULL, *tailr = NULL;

        // Keep the original command line strings.
        char *num1 = argv[1];
        char *num2 = argv[3];

        // Skip the sign before creating the linked list.
        if (num1[0] == '+' || num1[0] == '-')
            num1++;

        if (num2[0] == '+' || num2[0] == '-')
            num2++;

        // Create linked list for first number.
        if (createlist(&head1, &tail1, num1) == FAILURE)
        {
            printf("Failed to create First List\n");
            return FAILURE;
        }

        // Create linked list for second number.
        if (createlist(&head2, &tail2, num2) == FAILURE)
        {
            printf("Failed to create Second List\n");

            free_list(&head1);

            return FAILURE;
        }

        // Division by zero is not allowed.
        if (head2->data == 0 && head2 == tail2)
        {
            printf("Division by zero is not possible\n");

            free_list(&head1);
            free_list(&head2);

            return FAILURE;
        }

        // Zero divided by a non-zero number gives zero.
        if (head1->data == 0 && head1 == tail1)
        {
            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : 0\n");

            free_list(&head1);
            free_list(&head2);

            break;
        }

        // If both numbers are equal, the result is 1.
        if (list_compare(head1, head2) == 0)
        {
            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : ");

            // Different signs give a negative result.
            if (sign1 != sign2)
                printf("-");
            printf("1\n");

            free_list(&head1);
            free_list(&head2);

            break;
        }

        // Any number divided by 1 gives the same number.
        if (head2->data == 1 && head2 == tail2)
        {
            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : ");

            // Check the signs before printing the result.
            if (sign1 != sign2)
                printf("-");

            print_list(head1);

            free_list(&head1);
            free_list(&head2);

            break;
        }

        // If dividend is smaller than divisor, integer result is zero.
        if (list_compare(head1, head2) < 0)
        {
            printf("Operand 1 : %s\n", argv[1]);
            printf("Operator : %s\n", argv[2]);
            printf("Operand 2 : %s\n", argv[3]);
            printf("Output : 0\n");

            free_list(&head1);
            free_list(&head2);

            break;
        }

        // Perform normal division for the remaining cases.
        if (division(&head1, &tail1,
                     &head2, &tail2,
                     &headr, &tailr) == FAILURE)
        {
            printf("Division Failed\n");

            free_list(&head1);
            free_list(&head2);
            free_list(&headr);

            return FAILURE;
        }

        printf("Operand 1 : %s\n", argv[1]);
        printf("Operator : %s\n", argv[2]);
        printf("Operand 2 : %s\n", argv[3]);
        printf("Output : ");

        // If signs are different, division result is negative.
        if (sign1 != sign2)
            printf("-");

        print_list(headr);

        // Free all lists before leaving this operation.
        free_list(&head1);
        free_list(&head2);
        free_list(&headr);

        break;
    }

    // If the user enters an operator other than +, -, x, * or /.
    default:
    {
        printf("Invalid operator\n");
        return FAILURE;
    }
    }

    // Program completed successfully.
    return SUCCESS;
}