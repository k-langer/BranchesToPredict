#include "btb.h"
#include "decode.h"
#include "readva.h" 

char * readAndParse(FILE *inFilePtr, int *PA, char **instr) { 
        char *statusString;
        char lineString[MAXLINELENGTH];
        char *PAstr; 
        statusString = fgets(lineString, MAXLINELENGTH, inFilePtr);

        if (statusString) {
            //PAstr = (char *)strtok( "0x", " ");    
            //*instr = (char *)strtok(" ", "\n");    
            //*PA = (int)strtol( PAstr, NULL,  16);    
        }
        return statusString; 

}

int main() {
    //Parse trace 
    char * inFileString = "trace.txt"; 
    FILE *inFilePtr = fopen(inFileString, "r");
    istream_t * VAs = readimem(inFilePtr); 
    while (VAs) {
        printf("%llx %s\n",VAs->pc,VAs->instr); 
        VAs = VAs->next; 
    }
    /*
    char *inFileString = "trace.txt";
    FILE *inFilePtr = fopen(inFileString, "r");
    if (inFilePtr==NULL) { return 0; } 
    char *instr; 
    int PA; 
    char * neof = (char*)1;
    while (neof) {
        neof = readAndParse(inFilePtr, &PA, &instr); 
        printf("%d\n",PA);
    } 
    */ 
    //init BTB
    //feedback from decoders
    return 0;
}
