# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g

# the build target executable:
TARGET = main

all: compile-64

.PHONY: clean compile-32 compile-64 run

compile-32: $(TARGET).cpp
	$(CC) -m32 $(CFLAGS) -o $(TARGET) $(TARGET).cpp

compile-64: $(TARGET).cpp
	$(CC) -m64 $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)

run:
	@./$(TARGET) | c++filt -t
