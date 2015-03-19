#include"engine.h"

void run(istream_t * VAs, entry_t * btb) {
    unsigned long long pc,nextpc,predpc;
    char * instr = "";  
    int len; 
    while (VAs->next) {
        btb_index_t idx = btb_index(predpc-len);
        if (nextpc != predpc) {
            //Mispredict
            btb_train(btb,idx, nextpc);
            printf("BRANCH %llx %s\n",nextpc,instr); 
        }
        //printf("Fetch window: %d\n",idx.index);
        //printf("%d\n",btb_index(instr).index);
        //printf("%d\n",btb_index(instr).tag);
        //printf("%llx %s %d\n",nextpc,instr,decode_branchFound(instr));
        len = VAs->ilen; 
        predpc = VAs->pc+len; 
        instr = VAs->instr; 
        VAs = VAs->next; 
        nextpc = VAs->pc; 
    }
}
