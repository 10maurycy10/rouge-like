#pragma once
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int asprintf(char** dest, char* fmt, ...) {
    va_list args;
    va_start(args,256);
    va_list args2;
    va_copy(args2,args);
    *dest = malloc(vsnprintf(NULL, 0, fmt, args2) + 1);
    va_end(args2);
    va_copy(args2,args);
    vsprintf(*dest,fmt, args2);
    va_end(args2);
    va_end(args);
    return 0;
}