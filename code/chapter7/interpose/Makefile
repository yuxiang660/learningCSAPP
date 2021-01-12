compile: clean
	gcc -DCOMPILETIME -c mymalloc.c
	gcc -DCOMPILETIME -I. -o main main.c mymalloc.o
	./main

# -Wl,--warp,malloc means that "malloc" to "__wrap_malloc" and "__real_malloc" to "malloc"
link: clean
	gcc -DLINKTIME -c mymalloc.c
	gcc -c main.c
	gcc -Wl,--wrap,malloc -Wl,--wrap,free -o main main.o mymalloc.o
	./main

# PRELOAD for malloc func cannot work if it has printf func, which cause segmentation fault
run: clean
	gcc -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.c -ldl
	gcc -o main main.c
	export LD_PRELOAD="./mymalloc.so" && ./main

clean:
	@rm -rf *.o *.so main
