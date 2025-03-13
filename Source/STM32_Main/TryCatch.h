#ifndef _TRYCATCH_H_
#define _TRYCATCH_H_

#include "stdio.h"
#include "setjmp.h"

// Declare the buffer for setjmp/longjmp
extern jmp_buf buf;
extern int exception_value;

// Define TRY, CATCHALL, CATCH, and THROW macros for exception handling
#define TRY if ((exception_value = setjmp(buf)) == 0)
#define CATCHALL else
#define CATCH(NUM) else if (exception_value == NUM)
#define THROW(NUM) longjmp(buf, NUM)

#endif // _TRYCATCH_H_
