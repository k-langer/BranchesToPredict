#include"engine.h"

void run(istream_t * VAs, entry_t * btb) {
    unsigned long long pc,nextpc,predpc,prevpc;
    char * instr = "";  
    int len;
    unsigned long long branches = 0, mispreds = 0;  
    while (VAs->next) {
        btb_index_t idx = btb_index(predpc-len);
        //if ( decode_branchFound(instr) && nextpc != predpc) {
        if ( nextpc != prevpc && nextpc != predpc) {
            if (!decode_branchFound(instr)) { printf("%s\n",instr); }
            //Mispredict
            btb_train(btb,idx,nextpc);
            //printf("BRANCH %llx %d %s\n",nextpc,len,instr); 
            mispreds++; 
        }
        //Decoded branches
        if (decode_branchFound(instr)) { branches++; }
        len = VAs->ilen; 
        prevpc = VAs->pc; 
        instr = VAs->instr; 
        //printf("%llx %s\n",prevpc,instr);
        //Make prediction  
        predpc = btb_nextPc(btb, *VAs);
        VAs = VAs->next; 
        nextpc = VAs->pc; 
        //printf("Fetch window: %d\n",idx.index);
        //printf("%d\n",btb_index(instr).index);
        //printf("%d\n",btb_index(instr).tag);
    }
    printf("%f\n",(1-mispreds/(branches+0.0)));
}
