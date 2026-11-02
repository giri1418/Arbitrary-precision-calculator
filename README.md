Arbitrary Precision Calculator (APC) in C
Overview
The Arbitrary Precision Calculator (APC) is a command-line calculator written in C. It performs arithmetic operations on large integers that may exceed the limits of standard C data types such as int and long.

Instead of storing the complete number in a built-in numeric type, the program stores each digit in a doubly linked list and performs arithmetic digit by digit.
Features
- Addition (+)
- Subtraction (-)
- Multiplication (* or x)
- Division (/)
- Handles positive and negative integer operands
- Uses doubly linked lists for large-number representation
- Includes input-character validation and division-by-zero checking
- Dynamically allocates and frees linked-list nodes
Division produces an integer quotient; fractional/remainder output is not displayed.

Data Structure
Each digit is stored in an individual node:
typedef struct APC_Calculator
{
    data_t data;
    struct APC_Calculator *prev;
    struct APC_Calculator *next;
} apc;
The linked list maintains both head and tail pointers. This allows the program to traverse digits from either direction, which is useful for arithmetic operations.
Project Structure
giri_APC/
├── main.c          # Reads command-line arguments and selects the operation
├── createlist.c    # Creates, compares, prints and frees digit lists
├── operations.c    # Implements arithmetic operations
└── APC.h           # Structure definitions, macros and function declarations
Note: The uploaded source archive contains the header as apc.h, while the C files include APC.h. On case-sensitive systems such as Linux, filenames are case-sensitive. Rename apc.h to APC.h (recommended) or update the include statements consistently before compiling.
Requirements
- GCC compiler
- Linux terminal / WSL (or another environment with a C compiler)
Compilation
From inside the project directory, compile the source files:
gcc main.c createlist.c operations.c -o apc
If you get a header-file error, check that the header filename and the #include "APC.h" statements use exactly the same capitalization.
Usage
Run the executable with two integer operands and an operator:
./apc <operand1> <operator> <operand2>
Examples
Addition
./apc 12345678901234567890 + 98765432109876543210
Subtraction
./apc 98765432109876543210 - 12345678901234567890
Multiplication
./apc 12345678901234567890 '*' 10
Division
./apc 10000000000000000000 / 25
Negative numbers
./apc -500 + 200
./apc -500 '*' -20
Use quotes around * in shells where it may be expanded as a wildcard.
How It Works
1. The program accepts two operands and an arithmetic operator through command-line arguments.
2. Each operand is converted into a doubly linked list, with one digit stored per node.
3. The selected arithmetic function processes the digits:
   - Addition: adds digits from right to left and carries when required.
   - Subtraction: subtracts digits from right to left and borrows when required.
   - Multiplication: creates partial products and adds them to form the result.
   - Division: processes the dividend digit by digit to build the integer quotient.
4. The result is printed to the terminal.
5. Dynamically allocated linked-list memory is released.
Concepts Used
- C programming
- Structures and pointers
- Doubly linked lists
- Dynamic memory allocation (malloc and free)
- Command-line arguments (argc and argv)
- Modular programming using header and source files
- Arithmetic algorithms: carry, borrow and partial products
Limitations
- Only integer arithmetic is supported.
- Division returns the integer quotient; decimal precision and remainder are not displayed.
- Very large division operations may take longer because the current implementation repeatedly subtracts the divisor.
- Input must contain valid integer digits, optionally preceded by + or -.


Author
Kancharla Giri Babu


License
This project is available for learning and educational purposes. Add a license file if you intend to distribute it under a specific open-source license.