CC = gcc
CFLAGS  = -Og

TARGET = mstore
MAIN = main

all: prog

.PHONY: clean compile-32 compile-64 run

compile: $(TARGET).c
	$(CC) -S $(CFLAGS) -o $(TARGET).s $<

assemble: $(TARGET).c
	$(CC) -c $(CFLAGS) -o $(TARGET).o $<

clean:
	$(RM) $(TARGET).s $(TARGET).o $(MAIN)

disassemble: assemble
	objdump -d $(TARGET).o

prog: $(TARGET).c $(MAIN).c
	$(CC) $(CFLAGS) -o $(MAIN) $^

dump: prog
	objdump -d $(MAIN)
