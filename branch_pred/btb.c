#include "btb.h"

//Model of the BTB
entry_t * btb_init(int pwr2_sz) { 
    int size = pow(2,pwr2_sz); 
    btb_state.entries = (entry_t *)malloc(sizeof(entry_t)*size);
    btb_state.sz = pwr2_sz;
    return btb_state.entries;
}
unsigned long long btb_genTarget(unsigned long long tag, 
    unsigned long long index, unsigned long long offset) {
    unsigned long long target = (tag<<(btb_state.sz+PREDWIND)) | 
                                (index << PREDWIND) | 
                                offset;
    return target;
} 
btb_index_t btb_index(unsigned long long pc) {
    btb_index_t idx;
    unsigned long long fetchwindow = pow(2,PREDWIND)-1; 
    idx.offset = fetchwindow&pc; 
    unsigned long long pcsft = pc>>PREDWIND;
    //unsigned long long sz = 32;//pow(2,PREDWIND); 
    unsigned long long sz = pow(2,btb_state.sz);
    unsigned int msk = sz-1; 
    idx.index = msk&pcsft; 
    idx.tag = ( (~msk)&pcsft ) >> ilog2(sz);    
    unsigned long long assert_tag = btb_genTarget(idx.tag,idx.index,idx.offset);
    //if (assert_tag != pc) { printf("TAG BROKEN\n"); }    
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
    unsigned long long tag,index,offset,pc_tag; 
    tag = btb[idx.index].tag;
    offset = btb[idx.index].offset;
    index = idx.index;
    pc_tag = btb_genTarget(tag,index,offset);
    unsigned char match = btb[idx.index].val;
    match &= ( idx.tag == tag); 
    match &= (idx.offset == offset); 
    if (match) {
        //printf("%s\n",btb[idx.index].DEBUG_INSTR);
        //printf("BTB HIT %llx\n",btb[idx.index].target);
//        if (btb[idx.index].counter >= 2)
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
void btb_train(entry_t * btb, btb_index_t idx, unsigned long long target, char * instr) {
    //printf("Target %llx %llx\n",old,tag_match);
    btb_index_t tgt_idx = btb_index(target);
    entry_t * btbEntry = &btb[idx.index];
    btbEntry->val = TRUE;
    if (idx.index == tgt_idx.index
     && idx.tag   == tgt_idx.tag ) { 
        return; 
    }   
    if (btbEntry->target != target) {
        btb_state.evictions++;
        //long long pc = btb_genTarget(idx.tag,idx.index,idx.offset);
        //printf("%llx %s %d %d\n",pc,instr,idx.index,btb_state.evictions);
    }
    btbEntry->target = target; 
    btbEntry->tag = idx.tag;
    btbEntry->offset = idx.offset; 
    btbEntry->counter = 1;
    btbEntry->DEBUG_INSTR = instr;
}
void btb_trainCounter(entry_t * btb, btb_index_t idx, unsigned char dir) {
    entry_t * btbEntry = &btb[idx.index];
    if (btbEntry->val && idx.offset == btbEntry->offset && idx.tag == btbEntry->tag) { 
    } else {return;}
    if (dir != 0) {
       //NOT TAKEN
        btbEntry->counter = btbEntry->counter > 0 ? 
            btbEntry->counter-1 : 0;
    } else {
        //TAKEN
        btbEntry->counter = btbEntry->counter < 3 ? 
            btbEntry->counter+1 : 3;
    }
}
void btb_printDebug() {
    if (btb_state.sz <= 0) { return; } 
    for (int i = 0; i < pow(2,btb_state.sz); i++) {
        entry_t entry = btb_state.entries[i];
        unsigned long long address = btb_genTarget( 
            entry.tag, i, entry.offset);  
        if(!entry.val) { continue; }
        printf("%d Name: %s Target: 0x%llx Address: 0x%llx Counter: %d\n", i,
            entry.DEBUG_INSTR, entry.target, address, entry.counter);
    }
}
