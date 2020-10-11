CC = gcc
# Check whether -g take effect:
# > objdump -h hello.o | grep .debug_info
# > file hello
# print: with debug_info, not stripped
# > strip -s hello (stripped)
CFLAGS  = -g

TARGET = hello

all: link
debug: link-debug

.PHONY: clean pre-processor pre-processor-debug compile compile-debug assemble assemble-debug link link-debug

clean:
	/bin/sh -c 'rm -rf $(TARGET) $(TARGET).o $(TARGET).s $(TARGET).i'

pre-processor: $(TARGET).c
	$(CC) -E $< -o $(TARGET).i

pre-processor-debug: $(TARGET).c
	$(CC) -E -D DEBUG $< -o $(TARGET).i

compile: pre-processor
	$(CC) $(CFLAGS) -S $(TARGET).i -o $(TARGET).s

compile-debug: pre-processor-debug
	$(CC) $(CFLAGS) -S $(TARGET).i -o $(TARGET).s

assemble: compile
	$(CC) -c $(TARGET).s -o $(TARGET).o

assemble-debug: compile-debug
	$(CC) -c $(TARGET).s -o $(TARGET).o

link: assemble
	$(CC) $(TARGET).o -o $(TARGET)

link-debug: assemble-debug
	$(CC) $(TARGET).o -o $(TARGET)

run:
	@./$(TARGET)
