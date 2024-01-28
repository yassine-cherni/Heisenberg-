#include <stdio.h>

// Function prototypes
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);

// Function type definition for binary operations
typedef int (*BinaryOperation)(int, int);

// Function that applies a binary operation using a function pointer
int applyOperation(int a, int b, BinaryOperation operation) {
    return operation(a, b);
}

int main() {
    int num1 = 10, num2 = 5;

    // Function pointers assigned to different operations
    BinaryOperation addPtr = add;
    BinaryOperation subtractPtr = subtract;
    BinaryOperation multiplyPtr = multiply;

    // Apply the operations using function pointers
    printf("Addition: %d\n", applyOperation(num1, num2, addPtr));
    printf("Subtraction: %d\n", applyOperation(num1, num2, subtractPtr));
    printf("Multiplication: %d\n", applyOperation(num1, num2, multiplyPtr));

    return 0;
}

// Function definitions for binary operations
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int multiply(int a, int b) {
    return a * b;
}
