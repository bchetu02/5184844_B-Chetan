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

// Comparator for ascending
int compareAsc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Comparator for descending
int compareDesc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

// Count minimum swaps to match sorted order
int countSwaps(int arr_count, int* arr, int descending) {
    int (*pairs)[2] = malloc(arr_count * sizeof *pairs);
    for (int i = 0; i < arr_count; i++) {
        pairs[i][0] = arr[i];  // value
        pairs[i][1] = i;       // index
    }

    if (descending)
        qsort(pairs, arr_count, sizeof(pairs[0]), compareDesc);
    else
        qsort(pairs, arr_count, sizeof(pairs[0]), compareAsc);

    int* visited = calloc(arr_count, sizeof(int));
    int swaps = 0;

    for (int i = 0; i < arr_count; i++) {
        if (visited[i] || pairs[i][1] == i)
            continue;

        int cycle_size = 0;
        int j = i;
        while (!visited[j]) {
            visited[j] = 1;
            j = pairs[j][1];
            cycle_size++;
        }
        if (cycle_size > 1)
            swaps += (cycle_size - 1);
    }

    free(pairs);
    free(visited);

    return swaps;
}

int lilysHomework(int arr_count, int* arr) {
    // Copy array because countSwaps modifies indirectly
    int* arr_copy = malloc(arr_count * sizeof(int));
    memcpy(arr_copy, arr, arr_count * sizeof(int));
    int asc_swaps = countSwaps(arr_count, arr_copy, 0);

    memcpy(arr_copy, arr, arr_count * sizeof(int));
    int desc_swaps = countSwaps(arr_count, arr_copy, 1);

    free(arr_copy);

    return (asc_swaps < desc_swaps ? asc_swaps : desc_swaps);
}

// -------------------- HackerRank I/O helpers --------------------

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);
int parse_int(char*);

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));
    char** arr_temp = split_string(rtrim(readline()));

    int* arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int arr_item = parse_int(*(arr_temp + i));
        arr[i] = arr_item;
    }

    int result = lilysHomework(n, arr);
    fprintf(fptr, "%d\n", result);

    fclose(fptr);
    return 0;
}

// -------------------- Provided by HackerRank --------------------

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
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);
        data[data_length] = '\0';
    }
    return data;
}

char* ltrim(char* str) {
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
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
    return value;
}
