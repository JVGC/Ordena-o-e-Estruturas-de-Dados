objects = main.o pilha_double.o pilha_char.o RPN.o

all: $(objects)
	gcc -o main $(objects) -g -I.

main.o: main.c RPN.h
	gcc -c main.c

RPN.o: RPN.c RPN.h pilha_char.h pilha_double.h
	gcc -c RPN.c

pilha_char.o: pilha_char.c pilha_char.h
	gcc -c pilha_char.c

pilha_double.o: pilha_double.c pilha_double.h
	gcc -c pilha_double.c

clean:
	rm *.o main


run:
	./main