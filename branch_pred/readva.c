#include "readva.h"

istream_t * readimem(FILE *inFilePtr) { 
    unsigned long long i = 0;
    char str[30];  
    int len;
    istream_t * start = malloc(sizeof(istream_t)); 
    istream_t * nxt = start; 
    while (!feof(inFilePtr)) {
        fscanf(inFilePtr, "0x%llx   %s   %d\n",&i,str,&len);
        //printf("%llx\n",i);
        nxt->pc = i;
        nxt->ilen = len;
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
