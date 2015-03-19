#ifndef __decode__h
#define __decode__h
#include"readva.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAXLINELENGTH 1000
#define PREDWIND 5 

#define true 1 
#define false 0
typedef int bool;


const char * branchInstr;   
int decode_lengthDec(char * instr); 
bool decode_branchFound(char * instr); 
bool decode_branchMissed(istream_t * previnstr, unsigned long long pc); 

#endif
