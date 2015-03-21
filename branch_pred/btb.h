#ifndef __btb__h
#define __btb__h
#include<stdio.h>
#include<stdlib.h>
#include"readva.h"
#include "math.h"
#define PREDWIND 6
#define TRUE 1
#define FALSE 0 
typedef struct entry {
    unsigned char val;
    int index;
    int offset;  
    unsigned long long target; 
    int counter; 
    unsigned long long tag; 
    char * DEBUG_INSTR;
} entry_t;
typedef struct btb_index {
    unsigned long long index;
    unsigned long long offset;  
    unsigned long long tag; 
} btb_index_t; 
 
typedef struct metadata {
    int hits; 
    int misses; 
    int sz;
    int evictions; 
    entry_t * entries; 
} metadata_t; 

metadata_t btb_state; 
entry_t * btb_init(int pwr2_sz); 

//unsigned long long btb_read(entry_t * btb, unsigned long long pc); 
void btb_train(entry_t * btb, btb_index_t idx, unsigned long long target, char * instr); 
btb_index_t btb_index(unsigned long long pc); 
entry_t btb_read(entry_t * btb, unsigned long long pc);
unsigned long long btb_readTgt(entry_t btbEntry, unsigned long long pc);
unsigned long long btb_nextPc(entry_t * btb, istream_t instr); 
unsigned long long btb_genTarget(unsigned long long tag, 
    unsigned long long index, unsigned long long offset);
void btb_printDebug();

static inline unsigned int ilog2(const unsigned int x) {
  unsigned int y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}

#endif
