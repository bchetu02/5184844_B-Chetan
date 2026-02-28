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

// Helper: generate first q primes
void generate_primes(int q, int *primes) {
    int count = 0, num = 2;
    while (count < q) {
        int is_prime = 1;
        for (int i = 2; i*i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
        if (is_prime) {
            primes[count++] = num;
        }
        num++;
    }
}

int* waiter(int number_count, int* number, int q, int* result_count) {
    int *primes = malloc(q * sizeof(int));
    generate_primes(q, primes);

    int *stackA = malloc(number_count * sizeof(int));
    memcpy(stackA, number, number_count * sizeof(int));
    int sizeA = number_count;

    int *result = malloc(number_count * sizeof(int));
    int res_index = 0;

    for (int i = 0; i < q; i++) {
        int *stackB = malloc(sizeA * sizeof(int));
        int sizeB = 0;
        int *nextA = malloc(sizeA * sizeof(int));
        int nextA_size = 0;

        for (int j = sizeA - 1; j >= 0; j--) { // process from top to bottom
            if (stackA[j] % primes[i] == 0) {
                stackB[sizeB++] = stackA[j];
            } else {
                nextA[nextA_size++] = stackA[j];
            }
        }

        // Add stackB to result (top to bottom)
        for (int j = sizeB - 1; j >= 0; j--) {
            result[res_index++] = stackB[j];
        }

        free(stackA);
        free(stackB);
        stackA = nextA;
        sizeA = nextA_size;
    }

    // Add remaining stackA (top to bottom)
    for (int j = sizeA - 1; j >= 0; j--) {
        result[res_index++] = stackA[j];
    }

    free(stackA);
    free(primes);

    *result_count = res_index;
    return result;
}

int main() {
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));
    int q = parse_int(*(first_multiple_input + 1));

    char** number_temp = split_string(rtrim(readline()));

    int* number = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        int number_item = parse_int(*(number_temp + i));
        *(number + i) = number_item;
    }

    int result_count;
    int* result = waiter(n, number, q, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%d\n", *(result + i));
    }

    fclose(fptr);
    return 0;
}

// --- Helper Functions ---

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
        if (!data) return '\0';
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
        data = realloc(data, data_length);
        if (!data) return '\0';
    } else {
        data = realloc(data, data_length + 1);
        if (!data) return '\0';
        data[data_length] = '\0';
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
        if (!splits) return splits;
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
