#include "decode.h"
const char * const BranchInstr[] = {
    "JO" ,    "JNO" ,    "JS" ,    "JNS" ,
    "JE"  ,   "JZ" ,   "JNE" ,    "JNZ" ,
    "JB" ,  "JNAE" ,   "JC" , "JNB" ,
    "JAE" , "JNC" , "JBE" , "JNA" ,
    "JA" , "JNBE"   "JL"   "JNGE" ,
    "JGE"   "JNL",    "JLE" , "JNG",  "JG" ,
    "JNL",    "JP",  "JPE", "JNP",
    "JPO", "JCXZ", "JECXZ" 
};     

bool decode_branchFound(char * instr) { 
    //printf("%p %p %p\n",instr,instr+1,instr+2);
    bool branchFound = 0; 
    if (!instr) { return branchFound; } 
    //for(char *p = instr;*p;++p) *p=*p>0x40&&*p<0x5b?*p|0x60:*p;
    branchFound |= instr[0] == 'j';
    if ( !(instr+1 && instr+2) ) { return branchFound; }
    branchFound |= (instr[0] == 'c' && instr[1] == 'a' && instr[2] == 'l'); 
    branchFound |= (instr[0] == 'r' && instr[1] == 'e' && instr[2] == 't'); 
    branchFound |= (instr[0] == 'r' && instr[1] == 'e' && instr[2] == 'p'); 
    return branchFound; 
}
bool decode_branchMissed(istream_t * previnstr, unsigned long long pc) {
    unsigned long long predpc = previnstr->pc; 
    int len = previnstr->ilen; 
    return !( (len+predpc) == pc); 
}
//Faked decoder

