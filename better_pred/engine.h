#ifndef __engine__h
#define __engine__h
#include"readva.h"
#include"decode.h"
#include"typedefs.h"
#include"btb.h"
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define TAKEN 1
#define NOTTAKEN 0 
void run(istream_t * VAs, btb_entry_t * btb);

#endif
