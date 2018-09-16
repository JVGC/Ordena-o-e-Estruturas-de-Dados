#ifndef _HEAP_H_
#define _HEAP_H_

void heapsort(int* vet, int n, int* c, int* m);

void max_heapify(int* vet, int n, int position, int* c, int* m);
void build_max_heap(int* vet, int n, int* c, int* m);

#endif