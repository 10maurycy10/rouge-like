#pragma once
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int asprintf(char** dest, char* fmt, ...) {
    va_list args;
    va_start(args,256);
    va_list args2;
    va_list args3;
    va_copy(args2,args);
    *dest = malloc(1024);//_vscprintf(fmt,_VA_LIST args2)); //TODO THIS BUFFER
    va_copy(args3,args);
    sprintf(*dest,fmt, _VA_LIST args3);
    return 0;
}