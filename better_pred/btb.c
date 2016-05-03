#include "btb.h"

btb_entry_t * btb_init(int pwr2_sz, unsigned int ways) 
{
    int size = pow(2,pwr2_sz); 
    btb_state.entries = (btb_entry_t *)calloc(sizeof(btb_entry_t),size);
    btb_state.sz = size;
    return btb_state.entries;
} 
void btb_train(decode_redirect_t * redirect) 
{
    if (redirect->valid == 0) { return; } 
    unsigned long long pc = redirect->prevpc; 
    unsigned long long target = redirect->pc; 
    unsigned int ilen = redirect->ilen;
    btb_entry_t * entry = &btb_state.entries[btb_index(pc).index]; 
    entry->valid = 1; 
    entry->pc = pc&((unsigned int)(-1*63));
    //entry->endPtr = pc&(64-1); 
    entry->endPtr = 63; 
    entry->target = target; 
    if (redirect->isBranch) { entry->endPtr = (pc)&(64-1); }
    else if ( (pc)&(64-1)+ilen > 63 ) { 
        entry->endPtr = (pc)&(64-1); 
        entry->target = entry->pc+64;
    }
} 
btb_index_t btb_index(unsigned long long pc) 
{
	btb_index_t idx;
	idx.index = pc % btb_state.sz;  
	return idx; 
}
btb_tag_t btb_tag(unsigned long long pc) 
{
	btb_tag_t tag;
	tag.tag = pc/btb_state.sz; 
	tag.val = 1;
	return tag; 
}
btb_entry_t btb_read(btb_index_t * idx, btb_tag_t * tag) 
{
	btb_entry_t entry;
    entry.valid = 0;
    /*
	unsigned int entries, ways; 
	for ( entries = 0; entries < btb_state.sz; entries++) {
		if (idx->index == btb_state.entries[entries].index.index) {
			return btb_state.entries[entries]; 
	    }
    }
    */
    if (btb_state.entries[idx->index].valid) { return btb_state.entries[idx->index]; } 
	return entry; 
}
void btb_printDebug()
{
}

