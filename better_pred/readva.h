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
    unsigned long long prevpc;
    char * instr;  
    int ilen;
    unsigned char isBranch;  
    struct istream *  next; 
} istream_t; 

istream_t * readimem(FILE *inFilePtr);
#endif
