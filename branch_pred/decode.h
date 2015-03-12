#ifndef __decode__h
#define __decode__h
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAXLINELENGTH 1000

#define true 1 
#define false 0
typedef int bool;


const char * branchInstr;   
int decode_lengthDec(char * instr); 
bool decode_branchFound(char * instr); 

#endif
