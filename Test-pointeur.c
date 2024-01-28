#include <stdio.h>

// Function prototype
void myFunction(int x);

int main() {
    // Declare a function pointer
    void (*functionPointer)(int);

    // Assign the address of the function to the pointer
    functionPointer = &myFunction;

    // Call the function using the pointer
    (*functionPointer)(5);

    return 0;
}

// Function definition
void myFunction(int x) {
    printf("Value passed to myFunction: %d\n", x);
}
