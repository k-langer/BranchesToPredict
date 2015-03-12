#include "btb.h"

entry_t * btb_init(int pwr2_sz) { 
    btb_state = malloc(sizeof(metadata_t));
    int size = pow(2,pwr2_sz);  
    btb_state->entries = (entry_t *)malloc(sizeof(entry_t)*size);
    btb_state->sz = pwr2_sz;
} 
void btb_train(int index, int dir){ 
}
int btb_index(int PA) { 
    int sz_msk = btb_state->sz-1; 
    return PA&sz_msk; 
}
//Model of the BTB
