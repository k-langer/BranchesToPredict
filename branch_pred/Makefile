CC=gcc
CFLAGS=-std=gnu99 -Wno-unused-result -lm -g
WARNING=-Wall
OUTDIR = build
TARGET= BranchPred
_OBJS = btb.o \
	decode.o \
    readva.o \
    main.o
 
OBJS = $(patsubst %,$(OUTDIR)/%,$(_OBJS))

all: $(TARGET)

$(OUTDIR)/%.o: %.c 
	$(CC) -c $(CFLAGS) $^ -o $@

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

run: 
	./BranchPred

clean:  
	rm -f *.o build/*.o BranchPred
