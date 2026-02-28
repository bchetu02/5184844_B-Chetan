#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

// Min-heap helper functions
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(int *heap, int i) {
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapify_down(int *heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest]) smallest = left;
    if (right < size && heap[right] < heap[smallest]) smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify_down(heap, size, smallest);
    }
}

void push(int *heap, int *size, int value) {
    heap[*size] = value;
    heapify_up(heap, *size);
    (*size)++;
}

int pop(int *heap, int *size) {
    if (*size == 0) return -1;
    int min_val = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify_down(heap, *size, 0);
    return min_val;
}

int cookies(int k, int A_count, int* A) {
    int *heap = malloc(A_count * sizeof(int));
    int size = 0;

    for (int i = 0; i < A_count; i++) {
        push(heap, &size, A[i]);
    }

    int operations = 0;
    while (size >= 2 && heap[0] < k) {
        int least = pop(heap, &size);
        int second_least = pop(heap, &size);
        int new_cookie = least + 2 * second_least;
        push(heap, &size, new_cookie);
        operations++;
    }

    int result = (size > 0 && heap[0] >= k) ? operations : -1;
    free(heap);
    return result;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));
    int n = parse_int(*(first_multiple_input + 0));
    int k = parse_int(*(first_multiple_input + 1));

    char** A_temp = split_string(rtrim(readline()));
    int* A = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        A[i] = parse_int(*(A_temp + i));
    }

    int result = cookies(k, n, A);
    fprintf(fptr, "%d\n", result);

    free(A);
    fclose(fptr);
    return 0;
}

// --- HackerRank helper functions (unchanged) ---
char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);
        if (!line) break;
        data_length += strlen(cursor);
        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') break;
        alloc_length <<= 1;
        data = realloc(data, alloc_length);
        if (!data) { data = '\0'; break; }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);
        if (data) data[data_length] = '\0';
    }
    return data;
}

char* ltrim(char* str) {
    if (!str) return '\0';
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return '\0';
    char* end = str + strlen(str) - 1;
    while (end >= str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");
    int spaces = 0;
    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        splits[spaces - 1] = token;
        token = strtok(NULL, " ");
    }
    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0') exit(EXIT_FAILURE);
    return value;
}
