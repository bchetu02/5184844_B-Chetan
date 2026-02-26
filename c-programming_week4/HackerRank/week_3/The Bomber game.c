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

char** full_bombs(int r, int c) {
    char** grid = malloc(r * sizeof(char*));
    for (int i = 0; i < r; i++) {
        grid[i] = malloc(c + 1);
        memset(grid[i], 'O', c);
        grid[i][c] = '\0';
    }
    return grid;
}

char** explode(char** grid, int r, int c) {
    char** result = full_bombs(r, c);
    int dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (grid[i][j] == 'O') {
                result[i][j] = '.';
                for (int k = 0; k < 4; k++) {
                    int ni = i + dr[k], nj = j + dc[k];
                    if (ni >= 0 && ni < r && nj >= 0 && nj < c) {
                        result[ni][nj] = '.';
                    }
                }
            }
        }
    }
    return result;
}

char** copy_grid(char** grid, int r, int c) {
    char** new_grid = malloc(r * sizeof(char*));
    for (int i = 0; i < r; i++) {
        new_grid[i] = malloc(c + 1);
        strcpy(new_grid[i], grid[i]);
    }
    return new_grid;
}

/*
 * Complete the 'bomberMan' function below.
 */
char** bomberMan(int n, int grid_count, char** grid, int* result_count) {
    int c = strlen(grid[0]);
    *result_count = grid_count;

    if (n == 1) return copy_grid(grid, grid_count, c);
    if (n % 2 == 0) return full_bombs(grid_count, c);

    char** first = explode(grid, grid_count, c);
    if (n % 4 == 3) return first;

    char** second = explode(first, grid_count, c);
    return second;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int r = parse_int(*(first_multiple_input + 0));
    int c = parse_int(*(first_multiple_input + 1));
    int n = parse_int(*(first_multiple_input + 2));

    char** grid = malloc(r * sizeof(char*));
    for (int i = 0; i < r; i++) {
        char* grid_item = readline();
        *(grid + i) = grid_item;
    }

    int result_count;
    char** result = bomberMan(n, r, grid, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));
        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");
    fclose(fptr);

    return 0;
}

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
        if (!data) data = '\0';
    } else {
        data = realloc(data, data_length + 1);
        if (!data) data = '\0';
        else data[data_length] = '\0';
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
    while (*str != '\0' && isspace(*str)) str++;
    return str;
}

char* rtrim(char* str) {
    if (!str) return '\0';
    if (!*str) return str;
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
