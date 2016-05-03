#ifndef __decode__h
#define __decode__h
#include"readva.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"typedefs.h"
#define MAXLINELENGTH 1000

#define true 1 
#define false 0
typedef int bool;


const char * branchInstr;   
int decode_lengthDec(char * instr); 
bool decode_branchFound(char * instr); 
bool decode_branchMissed(istream_t * previnstr, unsigned long long pc);
decode_redirect_t decode_redirectPc(unsigned long long pc, btb_entry_t* entry); 
unsigned long long decode_NeedPc(unsigned long long pc, btb_entry_t* entry); 
#endif
