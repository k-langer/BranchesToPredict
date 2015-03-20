#include "btb.h"

entry_t * btb_init(int pwr2_sz) { 
    int size = pow(2,pwr2_sz); 
    btb_state.entries = (entry_t *)malloc(sizeof(entry_t)*size);
    btb_state.sz = pwr2_sz;
    return btb_state.entries;
} 
btb_index_t btb_index(unsigned long long pc) {
    btb_index_t idx;
    unsigned long long fetchwindow = pow(2,6)-1; 
    idx.offset = fetchwindow&pc; 
    unsigned long long pcsft = pc>>6;
    //unsigned long long sz = 32;//pow(2,PREDWIND); 
    unsigned long long sz = pow(2,btb_state.sz);
    unsigned int msk = sz-1; 
    idx.index = msk&pcsft; 
    idx.tag = ( (~msk)&pcsft ) >> ilog2(sz);    
    return idx;
}
entry_t btb_read(entry_t * btb, unsigned long long pc) {
    unsigned long long tag, target; 
    btb_index_t idx = btb_index(pc); 
    entry_t btbEntry = btb[idx.index];
    return btbEntry; 
}   
unsigned long long btb_nextPc(entry_t * btb, istream_t instr) {
    unsigned long long nextSeq = instr.nxtSeq;
    btb_index_t idx = btb_index(instr.pc); 
    //long long int pc_tag = (idx.tag<<11) | (idx.index << 6) | idx.offset;  
    unsigned long long tag,index,offset; 
    tag = btb[idx.index].tag;
    offset = btb[idx.index].offset;
    index = idx.index;
    unsigned long long pc_tag = (tag<<(btb_state.sz+6)) | (index << 6) | offset;  
    unsigned char match = btb[idx.index].val;
    match &= (instr.pc == pc_tag); 
    //printf("%s %llx %llx\n",instr.instr,instr.pc,pc_tag);
    if (match) {
        //printf("BTB HIT %llx\n",btb[idx.index].target);
        return btb[idx.index].target;
    }
    return nextSeq;
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
    //printf("Target %llx %llx\n",old,tag_match);
    entry_t * btbEntry = &btb[idx.index];
    btbEntry->target = target; 
    btbEntry->tag = idx.tag;
    btbEntry->offset = idx.offset; 
    btbEntry->val = TRUE;
}
//Model of the BTB
