all: target

target:
	gcc -g main.c sum.c -o main

clean:
	@rm -rf *.o *.s *.i main core

cpp:
	cpp main.c main.i
	cpp sum.c sum.i

cc1: cpp
	gcc -S main.i -g -o main.s
	gcc -S sum.i -g -o sum.s

as: cc1
	as -o main.o main.s
	as -o sum.o sum.s

ld: as
	ld -o main main.o sum.o

enable_core_dump:
	ulimit -c unlimited
	sudo systemctl disable apport.service
