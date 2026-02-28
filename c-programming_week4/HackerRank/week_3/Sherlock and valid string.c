#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

char* readline();

/*
 * Function to check if the string is valid
 */
char* isValid(char* s) {
    static char yes[] = "YES";
    static char no[] = "NO";

    if (!s || s[0] == '\0') {
        return yes; // empty string is considered valid
    }

    int freq[26] = {0};

    // Count frequencies (case-insensitive)
    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha((unsigned char)s[i])) {
            char ch = tolower((unsigned char)s[i]);
            freq[ch - 'a']++;
        }
    }

    // Count how many times each frequency occurs
    int freqCount[101] = {0};
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            freqCount[freq[i]]++;
        }
    }

    int uniqueFreq[2] = {0}, uniqueCount[2] = {0}, ufIndex = 0;

    for (int i = 1; i < 101; i++) {
        if (freqCount[i] > 0) {
            if (ufIndex < 2) {
                uniqueFreq[ufIndex] = i;
                uniqueCount[ufIndex] = freqCount[i];
                ufIndex++;
            } else {
                return no; // More than two frequency types
            }
        }
    }

    if (ufIndex == 1) {
        return yes; // All same frequency
    }

    if (ufIndex == 2) {
        // Case 1: One frequency is 1 and appears only once
        if ((uniqueFreq[0] == 1 && uniqueCount[0] == 1) ||
            (uniqueFreq[1] == 1 && uniqueCount[1] == 1)) {
            return yes;
        }

        // Case 2: Frequencies differ by 1 and the higher one appears only once
        if ((abs(uniqueFreq[0] - uniqueFreq[1]) == 1) &&
            ((uniqueCount[0] == 1 && uniqueFreq[0] > uniqueFreq[1]) ||
             (uniqueCount[1] == 1 && uniqueFreq[1] > uniqueFreq[0]))) {
            return yes;
        }
    }

    return no;
}

int main() {
    // Fallback: print to stdout if OUTPUT_PATH not set
    FILE* fptr = stdout;
    char* out_path = getenv("OUTPUT_PATH");
    if (out_path != NULL) {
        FILE* temp = fopen(out_path, "w");
        if (temp) fptr = temp;
    }

    char* s = readline();
    if (!s) {
        fprintf(fptr, "NO\n");
        if (fptr != stdout) fclose(fptr);
        return 1;
    }

    char* result = isValid(s);
    fprintf(fptr, "%s\n", result);

    free(s);
    if (fptr != stdout) fclose(fptr);
    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);
    if (!data) return NULL;

    while (true) {
        char* cursor = data + data_length;
        if (!fgets(cursor, alloc_length - data_length, stdin)) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length == 0 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length *= 2;
        char* new_data = realloc(data, alloc_length);
        if (!new_data) {
            free(data);
            return NULL;
        }
        data = new_data;
    }

    if (data_length > 0 && data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    } else {
        char* new_data = realloc(data, data_length + 1);
        if (new_data) {
            data = new_data;
        }
        data[data_length] = '\0';
    }

    return data;
}
