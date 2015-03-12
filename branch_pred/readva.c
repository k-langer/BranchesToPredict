#include "readva.h"

istream_t * readimem(FILE *inFilePtr) { 
    unsigned long long i = 0;
    char str[30];  
    istream_t * start = malloc(sizeof(istream_t)); 
    istream_t * nxt = start; 
    while (!feof(inFilePtr)) {
        fscanf(inFilePtr, "0x%llx   %s\n",&i,str);
        printf("%llx\n",i);
        nxt->pc = i;
        nxt->instr = malloc(strlen(str));
        memcpy(nxt->instr, str, strlen(str));
        if (!feof(inFilePtr))  {
            nxt->next = malloc(sizeof(istream_t));
            nxt = nxt->next; 
        }
    } 
    nxt = 0;  
    fclose(inFilePtr);
    return start;
} 
