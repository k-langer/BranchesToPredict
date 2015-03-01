#ifndef __btb__h
#define __btb__h
typedef struct entry {
    int index; 
    int target; 
    int counter; 
    int tag; 
} entry_t; 

entry_t * btb_init(int size); 
void btb_train(int index, int dir); 
int btb_index(int PA); 
#endif
