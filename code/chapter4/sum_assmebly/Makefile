all:

%.o:%.c
	gcc -c $<

%.s:%.c
	gcc -S $< -fverbose-asm

clean:
	rm -rf *.o *.s
