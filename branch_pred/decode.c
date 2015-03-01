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
//Faked decoder

