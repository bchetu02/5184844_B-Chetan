#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* highestValuePalindrome(char* s, int n, int k) {
    char* str = malloc((n + 1) * sizeof(char));
    strcpy(str, s);

    int* changed = calloc(n, sizeof(int));
    int used = 0;

    // Step 1: Make palindrome minimally
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - 1 - i]) {
            if (str[i] > str[n - 1 - i]) {
                str[n - 1 - i] = str[i];
            } else {
                str[i] = str[n - 1 - i];
            }
            changed[i] = changed[n - 1 - i] = 1;
            used++;
        }
    }

    if (used > k) {
        free(changed);
        free(str);
        char* impossible = malloc(3);
        strcpy(impossible, "-1");
        return impossible;
    }

    int remaining = k - used;

    // Step 2: Maximize palindrome
    for (int i = 0; i < n / 2 && remaining > 0; i++) {
        if (str[i] != '9') {
            if (changed[i] || changed[n - 1 - i]) {
                // already changed once, need only 1 more
                if (remaining >= 1) {
                    str[i] = str[n - 1 - i] = '9';
                    remaining--;
                }
            } else {
                // untouched, need 2 changes
                if (remaining >= 2) {
                    str[i] = str[n - 1 - i] = '9';
                    remaining -= 2;
                }
            }
        }
    }

    // Step 3: Handle middle digit (if odd length)
    if (n % 2 == 1 && remaining > 0) {
        str[n / 2] = '9';
    }

    free(changed);
    return str;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    char* s = malloc((n + 1) * sizeof(char));
    scanf("%s", s);

    char* result = highestValuePalindrome(s, n, k);
    printf("%s\n", result);

    free(s);
    free(result);
    return 0;
}
