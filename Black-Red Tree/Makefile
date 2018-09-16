objects = main.o rbtree.o

all: $(objects)
	gcc -o main $(objects) -g -I.

main.o: main.c rbtree.h
	gcc -c main.c
rbtree.o: rbtree.h rbtree.c
	gcc -c rbtree.c

clean:
	rm *.o main


run:
	./main
