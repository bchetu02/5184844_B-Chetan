#include <stdio.h>
#include <stdlib.h>

// Deque structure to store indices
typedef struct {
    int *data;
    int front, back;
} Deque;

Deque* createDeque(int n) {
    Deque* dq = malloc(sizeof(Deque));
    dq->data = malloc(n * sizeof(int));
    dq->front = dq->back = 0;
    return dq;
}

int isEmpty(Deque* dq) {
    return dq->front == dq->back;
}

void pushBack(Deque* dq, int x) {
    dq->data[dq->back++] = x;
}

void popBack(Deque* dq) {
    dq->back--;
}

void popFront(Deque* dq) {
    dq->front++;
}

int front(Deque* dq) {
    return dq->data[dq->front];
}

int back(Deque* dq) {
    return dq->data[dq->back - 1];
}

int* solve(int arr_count, int* arr, int queries_count, int* queries, int* result_count) {
    *result_count = queries_count;
    int* result = malloc(queries_count * sizeof(int));

    for (int qi = 0; qi < queries_count; qi++) {
        int d = queries[qi];
        Deque* dq = createDeque(arr_count);
        int* maxima = malloc((arr_count - d + 1) * sizeof(int));
        int idx = 0;

        // Process first d elements
        for (int i = 0; i < d; i++) {
            while (!isEmpty(dq) && arr[back(dq)] <= arr[i]) {
                popBack(dq);
            }
            pushBack(dq, i);
        }
        maxima[idx++] = arr[front(dq)];

        // Process rest of elements
        for (int i = d; i < arr_count; i++) {
            // Remove indices out of window
            while (!isEmpty(dq) && front(dq) <= i - d) {
                popFront(dq);
            }
            while (!isEmpty(dq) && arr[back(dq)] <= arr[i]) {
                popBack(dq);
            }
            pushBack(dq, i);
            maxima[idx++] = arr[front(dq)];
        }

        // Find minimum among maxima
        int minVal = maxima[0];
        for (int i = 1; i < idx; i++) {
            if (maxima[i] < minVal) minVal = maxima[i];
        }
        result[qi] = minVal;

        free(dq->data);
        free(dq);
        free(maxima);
    }
    return result;
}

int main() {
    int n, q;
    scanf("%d %d", &n, &q);

    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int* queries = malloc(q * sizeof(int));
    for (int i = 0; i < q; i++) scanf("%d", &queries[i]);

    int result_count;
    int* result = solve(n, arr, q, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        printf("%d\n", result[i]);
    }

    free(arr);
    free(queries);
    free(result);
    return 0;
}
