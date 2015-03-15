#include "btb.h"
#include "decode.h"
#include "readva.h" 

int main() {
    //Parse trace 
    char * inFileString = "trace.txt"; 
    FILE *inFilePtr = fopen(inFileString, "r");
    istream_t * VAs = readimem(inFilePtr); 
    unsigned long long pc;
    char * instr;  
    int num = 3104; 
    printf("%d\n",btb_index(num).index);
    printf("%d\n",btb_index(num).tag);
    while (VAs) {
        if (VAs->pc != pc) {
     //       printf("%llx %s\n",VAs->pc,VAs->instr); 
        }
        instr = VAs->instr; 
        pc = VAs->pc+VAs->ilen; 
        VAs = VAs->next; 
    }
    return 0;
}
