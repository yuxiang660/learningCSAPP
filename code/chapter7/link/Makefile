all: target

target:
	gcc -g main.c sum.c -o main

clean:
	@rm -rf *.o *.s *.i main core

cpp:
	cpp main.c main.i
	cpp sum.c sum.i

cc1: cpp
	/usr/lib/gcc/x86_64-linux-gnu/9/cc1 main.i -g -o main.s
	/usr/lib/gcc/x86_64-linux-gnu/9/cc1 sum.i -g -o sum.s

as: cc1
	as -o main.o main.s
	as -o sum.o sum.s

ld: as
	ld -o main main.o sum.o

enable_core_dump:
	ulimit -c unlimited
	sudo systemctl disable apport.service
