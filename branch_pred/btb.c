#include "btb.h"

entry_t * btb_init(int pwr2_sz) { 
    int size = pow(2,pwr2_sz); 
    btb_state.entries = (entry_t *)malloc(sizeof(entry_t)*size);
    btb_state.sz = pwr2_sz;
    return btb_state.entries;
} 
btb_index_t btb_index(unsigned long long pc) {
    btb_index_t idx;
    long long fetchwindow = pow(2,6)-1; 
    idx.offset = fetchwindow&pc; 
    unsigned long long pcsft = pc>>6;
    long long sz = pow(2,PREDWIND); 
    int msk = sz-1; 
    idx.index = msk&pcsft; 
    idx.tag = ( (~msk)&pcsft ) >> ilog2(sz);    
    return idx;
}
entry_t btb_read(entry_t * btb, unsigned long long pc) {
    btb_index_t idx = btb_index(pc); 
    unsigned long long tag, target; 
    entry_t btbEntry = btb[idx.index];
    return btbEntry; 
}   
unsigned long long btb_readTgt(entry_t btbEntry, unsigned long long pc) {
    btb_index_t idx = btb_index(pc); 
    unsigned long long tag, target; 
    target = btbEntry.target; 
    tag = btbEntry.tag; 
    if (btbEntry.val && tag == idx.tag) {
        return target; 
    }
    return 0;
}   
void btb_train(entry_t * btb, btb_index_t idx, unsigned long long target) { 
    entry_t * btbEntry = &btb[idx.index];
    btbEntry->target = target; 
    btbEntry->tag = idx.tag; 
    btbEntry->val = TRUE;
}
//Model of the BTB
