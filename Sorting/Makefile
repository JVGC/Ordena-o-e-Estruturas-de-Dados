objects = main.o insertion.o heap.o quick.o utils.o merge.o bubble.o

all: $(objects)
	gcc -o main $(objects) -g -lm -I.

main.o: main.c insertion.h utils.h bubble.h merge.h quick.h heap.h
	gcc -c main.c
insertion.o: insertion.c insertion.h utils.h
	gcc -c insertion.c

bubble.o: bubble.c bubble.h 
	gcc -c bubble.c	

merge.o: merge.c merge.h utils.h
	gcc -c merge.c

heap.o: heap.c heap.h utils.h
	gcc -c heap.c

quick.o: quick.c quick.h utils.h
	gcc -c quick.c
utils.o: utils.c utils.h
	gcc -c utils.c	

zip:
	zip EX13.zip main.c utils.h utils.c insertion.c insertion.h bubble.c bubble.h merge.c merge.h heap.c heap.h quick.c quick.h Makefile

clean:
	rm *.o


run:
	./main	