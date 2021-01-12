all: target

vec:
	gcc -shared -fpic -o libvec.so addvec.c multvec.c

target: vec
	gcc -o main main.c ./libvec.so

dlmain: vec
	gcc -rdynamic -o main dlmain.c -ldl

clean:
	@rm -rf *.o *.so main
