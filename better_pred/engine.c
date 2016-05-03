#include"engine.h"

void run(istream_t * VAs, btb_entry_t * btb) {
    unsigned long long pc,nextpc,predpc,prevpc;
    char * instr = "";  
    int len;
    decode_redirect_t redirect; 
    btb_entry_t entry; 
    btb_tag_t  tag; 
    btb_index_t idx;  
    unsigned long long branches = 0, mispreds = 0;  
    while (VAs->next) {

	pc = decode_NeedPc(VAs->pc, &entry); 
        idx = redirect.valid ? btb_index(redirect.pc) : btb_index(pc);
	tag = redirect.valid ? btb_tag(redirect.pc)  : btb_tag(pc);
	entry = btb_read(&idx,&tag); 
		
	redirect = decode_redirectPc(VAs->pc,&entry); 
	btb_train(VAs->pc,prevpc,&redirect); 
        
	len = VAs->ilen; 
        prevpc = VAs->pc; 
        instr = VAs->instr; 
        
	VAs = VAs->next; 
    }
    printf("Accuracy: %f\n",1-(mispreds/(branches+0.0)));
    printf("Branches: %llu\n",branches);
}
