#include "btb.h"

entry_t * btb_init(int pwr2_sz) { 
    btb_state = malloc(sizeof(metadata_t));
    int size = pow(2,pwr2_sz);  
    btb_state->entries = (entry_t *)malloc(sizeof(entry_t)*size);
    btb_state->sz = pwr2_sz;
} 
void btb_train(int index, unsigned long long target) { 
}
btb_index_t btb_index(unsigned long long pc) {
    btb_index_t idx; 
    unsigned long long pcsft = pc>>PREDWIND;
    long long sz = 32; 
    int msk = sz-1; 
    idx.index = msk&pcsft; 
    idx.tag = ( (~msk)&pcsft ) >> ilog2(sz);    
    return idx;
}
//Model of the BTB
