#ifndef __TYPES__h
#define __TYPES__h

typedef struct btb_entry {
    unsigned char val;
    unsigned long long pc;
    unsigned long long endPtr;
    unsigned long long target;
    unsigned int counter;
    unsigned long long tag;
    char * DEBUG_INSTR;
} btb_entry_t;
typedef struct btb_index {
    unsigned long long index;
    unsigned long long hashIndex;
    unsigned long long DEBUG_PC;
} btb_index_t;

typedef struct btb_tag {
    unsigned long long tag;
    unsigned int way;
    unsigned long long DEBUG_PC;
} btb_tag_t;

typedef struct decode_redirct {
    unsigned char valid;
    unsigned long long pc;
    unsigned long long DEBUG_PREVPC;
    char * DEBUG_INSTR;
} decode_redirect_t;


#endif
