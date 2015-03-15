#ifndef __btb__h
#define __btb__h
#include<stdio.h>
#include<stdlib.h>
#include "math.h"
#define PREDWIND 5 
typedef struct entry {
    int index; 
    unsigned long long target; 
    int counter; 
    unsigned long long tag; 
} entry_t;
typedef struct btb_index {
    int index; 
    unsigned long long tag; 
} btb_index_t; 
 
typedef struct metadata {
    int hits; 
    int misses; 
    int sz; 
    entry_t * entries; 
} metadata_t; 

metadata_t * btb_state; 
entry_t * btb_init(int pwr2_sz); 

unsigned long long btb_read(unsigned long long pc); 
void btb_train(int index, unsigned long long target); 
btb_index_t btb_index(unsigned long long pc); 

static inline unsigned int ilog2(const unsigned int x) {
  unsigned int y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}

#endif
