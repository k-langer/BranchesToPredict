#include "btb.h"
#include "decode.h"
#include "readva.h" 
#include "engine.h"
int main() {
    //Parse trace 
    char * inFileString = "trace.txt"; 
    FILE *inFilePtr = fopen(inFileString, "r");
    istream_t * VAs = readimem(inFilePtr); 

    entry_t * btb = btb_init(5);
    run(VAs,btb);    
    return 0;
}
