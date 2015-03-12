#ifndef __btb__h
#define __btb__h
#include<stdio.h>
#include<stdlib.h>
#include "math.h"
typedef struct entry {
    int index; 
    int target; 
    int counter; 
    int tag; 
} entry_t;
 
typedef struct metadata {
    int hits; 
    int misses; 
    int sz; 
    entry_t * entries; 
} metadata_t; 

metadata_t * btb_state; 
entry_t * btb_init(int pwr2_sz); 
void btb_train(int index, int dir); 
int btb_index(int PA); 
#endif
