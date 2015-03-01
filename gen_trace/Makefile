CC=gcc
CFLAGS=-std=gnu99 -Wno-unused-result -lm
WARNING=-Wall 
DEBUG=-g -O0
TARGET= RunTrace
OBJS = genTrace.o

all: $(TARGET)

%.o: %.c 
	$(CC) -c $(CFLAGS) $(WARNING) $(DEBUG) $^ -o $@

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(DEBUG)

run: 
	gdb -batch -x run.gdb RunTrace 2> /dev/null | grep "=>" | \
		awk '{print $$2," ",$$4}' | \
		gzip > trace.gz
clean:  
	rm -f *.o RunTrace trace.gz
