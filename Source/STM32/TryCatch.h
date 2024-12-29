#ifndef _TryCatch_H_
#define _TryCatch_H_

#include "stdio.h"
#include "setjmp.h"

jmp_buf buf;
int exception_value =0;

#define TRY if((exception_value)=setjmp(buf))==0)
#define CATCHALL else 
#define CATCH(NUM) else if(exception_value == NUM)
#define THROW(NUM) longjmp(buf,NUM)

#endif