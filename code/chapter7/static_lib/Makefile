all: target

vec:
	gcc -c addvec.c multvec.c
	ar rcs libvec.a addvec.o multvec.o

target: vec
	gcc -c main.c
	gcc -static -o main main.o ./libvec.a

# the rule to link static lib is to find unresolved symbols from left to right, then throw away
error_target: vec
	gcc -c main.c
	gcc -static ./libvec.a main.o -o main

clean:
	@rm -rf *.o *.a main
