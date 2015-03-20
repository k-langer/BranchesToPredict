#ifndef __readva__h
#define __readva__h
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <inttypes.h>

typedef struct istream 
{ 
    unsigned long long pc;
    unsigned long long nxtSeq; 
    char * instr;  
    int ilen; 
    struct istream *  next; 
} istream_t; 

istream_t * readimem(FILE *inFilePtr);
#endif
