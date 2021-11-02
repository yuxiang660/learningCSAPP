CC=g++
CFLAGS=-Wall -O1 -g
LCFLAGS=-O1
LEX = flex
LEXLIB = -lfl
YAS=./yas

all: yas

yas-grammar.c: yas-grammar.lex
	$(LEX) yas-grammar.lex
	mv lex.yy.c yas-grammar.c

# These are the explicit rules for making yis yas and hcl2c and hcl2v
yas-grammar.o: yas-grammar.c
	$(CC) $(LCFLAGS) -c yas-grammar.c

isa.o: isa.c isa.h
	$(CC) $(CFLAGS) -c isa.c

yas.o: yas.c yas.h isa.h
	$(CC) $(CFLAGS) -c yas.c

yas: yas.o yas-grammar.o isa.o
	$(CC) $(CFLAGS) yas-grammar.o yas.o isa.o ${LEXLIB} -o yas

test:
	$(YAS) test.ys
	cat test.yo

clean:
	rm -f *.o *.yo *.exe yis yas hcl2c mux4 *~ core.* 
	rm -f hcl.tab.c hcl.tab.h lex.yy.c yas-grammar.c
