#include "btb.h"
#include "decode.h"
#include "readva.h" 
#include "engine.h"
int main() {
    //Parse trace 
    char * inFileString = "trace.txt"; 
    FILE *inFilePtr = fopen(inFileString, "r");
    istream_t * VAs = readimem(inFilePtr); 

    entry_t * btb = btb_init(6);
    run(VAs,btb);    
    //btb_printDebug();
    return 0;
}
