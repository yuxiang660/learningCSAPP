CC = gcc
CFLAGS  = -Og

TARGET = mstore

all: compile assemble disassemble

.PHONY: clean compile-32 compile-64 run

compile: $(TARGET).c
	$(CC) -S $(CFLAGS) -o $(TARGET).s $<

assemble: $(TARGET).c
	$(CC) -c $(CFLAGS) -o $(TARGET).o $<

clean:
	$(RM) $(TARGET).s $(TARGET).o

disassemble: assemble
	objdump -d $(TARGET).o
