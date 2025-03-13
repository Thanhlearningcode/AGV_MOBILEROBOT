#include "TryCatch.h"
jmp_buf buf;
int exception_value = 0;
/*********************** 	How to use *********************************

void test_function() {
    // Simulate an exception
    THROW(42);  // This will jump to the CATCH block
}

int main() {
    TRY {
        // Try block: Normal execution
        printf("In TRY block\n");
        test_function();
        printf("This will not print because of exception\n");
    }
    CATCH(42) {
        // Catch block for exception number 42
        printf("Caught exception with code 42\n");
    }
    CATCHALL {
        // Catch block for any other exception
        printf("Caught an unknown exception\n");
    }
    return 0;
}  */ 
