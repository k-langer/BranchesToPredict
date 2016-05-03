#ifndef __btb__h
#define __btb__h
#include<stdio.h>
#include<stdlib.h>
#include"readva.h"
#include "math.h"
#include "typedefs.h"
#define PREDWIND 3
#define TRUE 1LL
#define FALSE 0LL
 
typedef struct metadata {
    int hits; 
    int misses; 
    int sz;
    int evictions; 
    btb_entry_t * entries; 
} metadata_t; 

metadata_t btb_state; 
btb_entry_t * btb_init(int pwr2_sz, unsigned int ways); 

//unsigned long long btb_read(entry_t * btb, unsigned long long pc); 
void btb_train(unsigned long long pc, unsigned long long target, decode_redirect_t * redirect); 
btb_index_t btb_index(unsigned long long pc); 
btb_tag_t btb_tag(unsigned long long pc); 
btb_entry_t btb_read(btb_index_t * idx, btb_tag_t * tag);
void btb_printDebug();

static inline unsigned long long ilog2(const unsigned int x) {
  unsigned int y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}

#endif
