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
    //branchFound |= (instr[0] == 's' && instr[1] == 'y' && instr[2] == 's'); 
    return branchFound; 
}
bool decode_branchMissed(istream_t * previnstr, unsigned long long pc) {
    unsigned long long predpc = previnstr->pc; 
    int len = previnstr->ilen; 
    return !( (len+predpc) == pc); 
}
decode_redirect_t decode_redirectPc(istream_t * misdInstr, btb_entry_t* entry) { 
	decode_redirect_t redirect;
    unsigned long long pc = misdInstr->pc; 
    if ( entry->valid == 0 || (entry->pc > pc) || (entry->pc+entry->endPtr < pc) ) {
        redirect.valid = 1; 
        redirect.pc = misdInstr->pc; 
        redirect.ilen = misdInstr->ilen; 
        redirect.prevpc= misdInstr->prevpc; 
        redirect.isBranch = misdInstr->isBranch; 
        redirect.isTaken = redirect.isBranch && redirect.prevpc+misdInstr->ilen != misdInstr->pc;
    }
	return redirect; 
} 
unsigned long long decode_NeedPc(unsigned long long pc, btb_entry_t* entry) {
	unsigned long long updPc;
    if ( !entry || entry->valid == 0 ) { return 0; } 
    if ( entry->pc+entry->endPtr == pc ) { return entry->target; }
	return pc;
} 
//Faked decoder

