#include <stdio.h>
#include <stdlib.h>

#define MAX 100000  // Max possible number of elements (adjust as per constraints)

int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;

// Push element to stack
void push(int stack[], int *top, int value) {
    stack[++(*top)] = value;
}

// Pop element from stack
int pop(int stack[], int *top) {
    return stack[(*top)--];
}

// Enqueue operation
void enqueue(int x) {
    push(stack1, &top1, x);
}

// Dequeue operation
void dequeue() {
    if (top2 == -1) { // Transfer elements only if stack2 is empty
        while (top1 != -1) {
            push(stack2, &top2, pop(stack1, &top1));
        }
    }
    if (top2 != -1) { // Pop from stack2 (front of queue)
        pop(stack2, &top2);
    }
}

// Print front element
void printFront() {
    if (top2 == -1) { // Transfer elements only if stack2 is empty
        while (top1 != -1) {
            push(stack2, &top2, pop(stack1, &top1));
        }
    }
    if (top2 != -1) { // Print front element
        printf("%d\n", stack2[top2]);
    }
}

int main() {
    int q;
    scanf("%d", &q); // number of queries

    while (q--) {
        int type, x;
        scanf("%d", &type);

        if (type == 1) { // Enqueue
            scanf("%d", &x);
            enqueue(x);
        } else if (type == 2) { // Dequeue
            dequeue();
        } else if (type == 3) { // Print front
            printFront();
        }
    }

    return 0;
}
