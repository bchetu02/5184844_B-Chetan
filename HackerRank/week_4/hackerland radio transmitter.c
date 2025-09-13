#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int hackerlandRadioTransmitters(int x_count, int* x, int k) {
    qsort(x, x_count, sizeof(int), compare); // Sort house positions

    int transmitters = 0;
    int i = 0;

    while (i < x_count) {
        transmitters++;

        int loc = x[i] + k; // Place transmitter within range
        while (i < x_count && x[i] <= loc)
            i++;

        loc = x[i - 1] + k; // Cover as many as possible
        while (i < x_count && x[i] <= loc)
            i++;
    }

    return transmitters;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int* x = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &x[i]);

    int result = hackerlandRadioTransmitters(n, x, k);
    printf("%d\n", result);

    free(x);
    return 0;
}
