#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int heap[MAX];
int size = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int i) {
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1, right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void insert(int x) {
    heap[size] = x;
    heapifyUp(size);
    size++;
}

void delete(int x) {
    for (int i = 0; i < size; i++) {
        if (heap[i] == x) {
            heap[i] = heap[size - 1];
            size--;
            heapifyDown(i);
            break;
        }
    }
}

int main() {
    int Q;
    scanf("%d", &Q);

    while (Q--) {
        int type, x;
        scanf("%d", &type);

        if (type == 1) { // Insert
            scanf("%d", &x);
            insert(x);
        } 
        else if (type == 2) { // Delete
            scanf("%d", &x);
            delete(x);
        } 
        else if (type == 3) { // Print min
            printf("%d\n", heap[0]);
        }
    }

    return 0;
}
