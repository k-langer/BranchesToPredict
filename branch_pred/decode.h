#ifndef __decode__h
#define __decode__h

#define true 1 
#define false 0
typedef int bool;


const char * branchInstr;   
int decode_lengthDec(char * instr); 
bool decode_branchFound(char * instr); 

#endif
