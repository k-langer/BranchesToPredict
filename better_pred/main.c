#include "btb.h"
#include "decode.h"
#include "readva.h" 
#include "engine.h"
#include "typedefs.h"
int main() {
    //Parse trace 
    char * inFileString = "trace.txt"; 
    FILE *inFilePtr = fopen(inFileString, "r");
    istream_t * VAs = readimem(inFilePtr); 

    btb_entry_t * btb = btb_init(10,1);
    run(VAs,btb);    
    //btb_printDebug();
    return 0;
}
