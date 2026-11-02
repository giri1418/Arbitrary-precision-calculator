#include "APC.h"

int addition(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr)
{
    // Start from the last digit because addition is done from right to left.
    apc *p = *tail1;
    apc *q = *tail2;

    // Carry is stored here when the sum of two digits is greater than 9.
    int carry = 0;

    // Continue until all digits of both numbers are processed.
    while (p || q)
    {
        // Start the sum with the previous carry.
        int sum = carry;

        // Add the current digit of first number.
        if (p)
        {
            sum = sum + p->data;
            p = p->prev;
        }

        // Add the current digit of second number.
        if (q)
        {
            sum = sum + q->data;
            q = q->prev;
        }

        // Create a new node for the result digit.
        apc *new = malloc(sizeof(apc));

        // If memory allocation fails, stop the operation.
        if (new == NULL)
            return FAILURE;

        // Store only the last digit of the sum.
        new->data = sum % 10;

        // New node is inserted at the beginning of result list.
        new->prev = NULL;
        new->next = *headr;

        // If result list already has nodes, connect the previous first node.
        if (*headr)
            (*headr)->prev = new;
        else
            // First created node becomes the last node also.
            *tailr = new;

        // Make the new node the first node of result list.
        *headr = new;

        // Get carry for the next digit.
        carry = sum / 10;
    }

    // If one carry is still left, add it to the result.
    if (carry)
    {
        apc *new = malloc(sizeof(apc));

        // Check memory allocation.
        if (new == NULL)
            return FAILURE;

        // Store the remaining carry as a new digit.
        new->data = carry;
        new->prev = NULL;
        new->next = *headr;

        // Connect the old first node with the new node.
        if (*headr)
            (*headr)->prev = new;

        // New node becomes the first node.
        *headr = new;
    }

    return SUCCESS;
}

int subtraction(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr)
{
    // Start subtraction from the last digit.
    apc *p = *tail1;
    apc *q = *tail2;

    // Borrow is used when the current digit of first number is smaller.
    int borrow = 0;

    // Process every digit of the first number.
    while (p != NULL)
    {
        // Get the current digit of first number.
        int n1 = p->data;

        // Assume second number has no digit at this position.
        int n2 = 0;

        // If second number has a digit, take its value.
        if (q != NULL)
            n2 = q->data;

        // Subtract both digits along with the previous borrow.
        int value = n1 - n2 - borrow;

        // If result becomes negative, borrow 1 from the next digit.
        if (value < 0)
        {
            value = value + 10;
            borrow = 1;
        }
        else
        {
            // No borrow is required for the next digit.
            borrow = 0;
        }

        // Create a node for the result digit.
        apc *new = malloc(sizeof(apc));

        // Check whether memory allocation was successful.
        if (new == NULL)
            return FAILURE;

        new->data = value;
        new->prev = NULL;
        new->next = *headr;

        // Insert the new digit at the beginning of result list.
        if (*headr != NULL)
            (*headr)->prev = new;
        else
            // First node is also the tail of result list.
            *tailr = new;

        *headr = new;

        // Move to the previous digit of first number.
        p = p->prev;

        // Move to the previous digit of second number if available.
        if (q != NULL)
            q = q->prev;
    }

    // Remove extra zeros from the beginning of the result.
    // Example: 005 becomes 5.
    while (*headr != *tailr && (*headr)->data == 0)
    {
        apc *temp = *headr;

        // Move head to the next node.
        *headr = (*headr)->next;

        // New head should not have a previous node.
        (*headr)->prev = NULL;

        // Delete the old zero node.
        free(temp);
    }

    return SUCCESS;
}

int multiplication(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr)
{
    // Start from the last digit of the second number.
    // Multiplication is performed digit by digit.
    apc *p = *tail2;

    // These lists store the final result and temporary multiplication result.
    apc *result_head = NULL, *result_tail = NULL;

    // Number of zeros to add at the end of each partial result.
    int count = 0;

    // Process every digit of the second number.
    while (p != NULL)
    {
        // Current digit of second number.
        int digit2 = p->data;

        // Carry for multiplication.
        int carry = 0;

        // Start from the last digit of first number.
        apc *q = *tail1;

        // Temporary list stores multiplication of first number by one digit.
        apc *temp_head = NULL, *temp_tail = NULL;

        // Multiply the current digit with every digit of first number.
        while (q != NULL)
        {
            // Multiply two digits and add previous carry.
            int mul = (q->data * digit2) + carry;

            // Take the last digit as the current result digit.
            int digit = mul % 10;

            // Remaining part becomes carry.
            carry = mul / 10;

            // Create a node for the result digit.
            apc *new = malloc(sizeof(apc));

            // Check memory allocation.
            if (new == NULL)
                return FAILURE;

            new->data = digit;
            new->prev = NULL;
            new->next = NULL;

            // First node of temporary list.
            if (temp_head == NULL)
            {
                temp_head = new;
                temp_tail = new;
            }
            else
            {
                // Insert the new digit at the beginning.
                new->next = temp_head;
                temp_head->prev = new;
                temp_head = new;
            }

            // Move to previous digit of first number.
            q = q->prev;
        }

        // If carry is left after processing all digits, add it.
        if (carry != 0)
        {
            apc *new = malloc(sizeof(apc));

            // Check memory allocation.
            if (new == NULL)
                return FAILURE;

            new->data = carry;
            new->prev = NULL;
            new->next = temp_head;

            // Connect carry node with temporary list.
            if (temp_head != NULL)
                temp_head->prev = new;
            else
                temp_tail = new;

            temp_head = new;
        }

        // Add zeros according to the position of the current digit.
        // These zeros are required for normal multiplication.
        int i = 0;

        while (i < count)
        {
            apc *new = malloc(sizeof(apc));

            // Check memory allocation.
            if (new == NULL)
                return FAILURE;

            // Add zero at the end of temporary result.
            new->data = 0;
            new->next = NULL;
            new->prev = temp_tail;

            // Connect the new zero node.
            if (temp_tail != NULL)
                temp_tail->next = new;
            else
                temp_head = new;

            temp_tail = new;

            i++;
        }

        // For the first partial result, no addition is needed.
        if (result_head == NULL)
        {
            result_head = temp_head;
            result_tail = temp_tail;
        }
        else
        {
            // Add the current partial result to the previous result.
            apc *new_head = NULL;
            apc *new_tail = NULL;

            if (addition(&result_head, &result_tail,
                         &temp_head, &temp_tail,
                         &new_head, &new_tail) == FAILURE)
            {
                return FAILURE;
            }

            // Update final result pointers.
            result_head = new_head;
            result_tail = new_tail;

            // Temporary list is no longer required.
            free_list(&temp_head);
        }

        // Next partial result needs one more zero.
        count++;

        // Move to previous digit of second number.
        p = p->prev;
    }

    // Return the final multiplication result to the caller.
    *headr = result_head;
    *tailr = result_tail;

    return SUCCESS;
}

int division(apc **head1, apc **tail1, apc **head2, apc **tail2, apc **headr, apc **tailr)
{
    // Start from the first digit of the dividend.
    apc *p = *head1;

    // rem list stores the current remainder during division.
    apc *rem_head = NULL;
    apc *rem_tail = NULL;

    // Result list is initially empty.
    *headr = NULL;
    *tailr = NULL;

    // Check for division by zero.
    if (*head2 == NULL || ((*head2)->data == 0 && *head2 == *tail2))
    {
        printf("Division by zero is not possible\n");
        return FAILURE;
    }

    // Process the dividend digit by digit.
    while (p != NULL)
    {
        // Add current dividend digit to remainder.
        apc *new = malloc(sizeof(apc));

        // Check memory allocation.
        if (new == NULL)
            return FAILURE;

        new->data = p->data;
        new->prev = rem_tail;
        new->next = NULL;

        // Attach the new digit to remainder list.
        if (rem_tail != NULL)
            rem_tail->next = new;
        else
            rem_head = new;

        rem_tail = new;

        // Remove leading zeros from remainder.
        while (rem_head != rem_tail && rem_head->data == 0)
        {
            apc *temp = rem_head;

            rem_head = rem_head->next;
            rem_head->prev = NULL;

            free(temp);
        }

        // Count how many times divisor can be subtracted from remainder.
        int count = 0;

        // Continue subtraction while remainder is greater than or equal
        // to the divisor.
        while (list_compare(rem_head, *head2) >= 0)
        {
            apc *new_head = NULL;
            apc *new_tail = NULL;

            // Subtract divisor from current remainder.
            if (subtraction(&rem_head, &rem_tail,
                            head2, tail2,
                            &new_head, &new_tail) == FAILURE)
            {
                free_list(&rem_head);
                free_list(headr);

                return FAILURE;
            }

            // Old remainder list is no longer needed.
            free_list(&rem_head);

            // New subtraction result becomes the current remainder.
            rem_head = new_head;
            rem_tail = new_tail;

            // One successful subtraction means quotient increases by one.
            count++;
        }

        // Store quotient digit in result list.
        new = malloc(sizeof(apc));

        // Check memory allocation.
        if (new == NULL)
        {
            free_list(&rem_head);
            free_list(headr);

            return FAILURE;
        }

        new->data = count;
        new->prev = *tailr;
        new->next = NULL;

        // Attach quotient digit to the result list.
        if (*tailr != NULL)
            (*tailr)->next = new;
        else
            *headr = new;

        *tailr = new;

        // Move to the next digit of dividend.
        p = p->next;
    }

    // Remove leading zeros from quotient.
    // Example: 00012 becomes 12.
    while (*headr != *tailr && (*headr)->data == 0)
    {
        apc *temp = *headr;

        *headr = (*headr)->next;
        (*headr)->prev = NULL;

        free(temp);
    }

    // If result list became empty, store zero as the result.
    if (*headr == NULL)
    {
        apc *new = malloc(sizeof(apc));

        // Check memory allocation.
        if (new == NULL)
        {
            free_list(&rem_head);
            return FAILURE;
        }

        new->data = 0;
        new->prev = NULL;
        new->next = NULL;

        *headr = new;
        *tailr = new;
    }

    // Remainder is no longer required after division.
    free_list(&rem_head);

    return SUCCESS;
}