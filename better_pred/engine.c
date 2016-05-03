#include"engine.h"

void run(istream_t * VAs, btb_entry_t * btb) {
    unsigned long long pc,nextpc,predpc,prevpc;
    char * instr = "";  
    int len;
    decode_redirect_t redirect; 
    btb_entry_t entry; 
    btb_tag_t  tag; 
    btb_index_t idx; 
    istream_t   prevFetch; 
     
    unsigned long long branches = 0, mispreds = 0; 
    while (VAs->next) {
	pc = decode_NeedPc(VAs->pc, &entry); 
    idx = redirect.valid ? btb_index(redirect.pc) : btb_index(pc);
	tag = redirect.valid ? btb_tag(redirect.pc)  : btb_tag(pc);
	entry = btb_read(&idx,&tag); 

	redirect = decode_redirectPc(&prevFetch,&entry); 
	btb_train(&redirect); 
	
    len = VAs->ilen; 
    prevpc = VAs->pc; 
    instr = VAs->instr; 
	VAs = VAs->next; 
    prevFetch.ilen = len; 
    prevFetch.prevpc=prevpc; 
    prevFetch.pc=VAs->pc;
    prevFetch.isBranch=decode_branchFound(instr);
    btb_state.instr_counter++; 
    if (prevFetch.isBranch) { branches++; }
    if (prevFetch.isBranch && redirect.valid){ mispreds++;}
    }
    printf("Accuracy: %f\n",1-(mispreds/(branches+0.0)));
    printf("Branches: %llu\n",branches);
}
