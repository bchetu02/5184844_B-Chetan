
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Define maximum limits
#define MAX_LEN 1000000
#define STACK_SIZE 100000

// Stack to store previous states for undo
char *history[STACK_SIZE];
int top = -1;

void push(const char *s) {
    if (top + 1 >= STACK_SIZE) return; // prevent overflow
    history[++top] = strdup(s); // allocate copy of string
}

char* pop() {
    if (top < 0) return NULL; // prevent underflow
    return history[top--];
}

int main() {
    int Q;
    scanf("%d", &Q);

    char *S = calloc(MAX_LEN + 1, sizeof(char)); // dynamically allocated main string
    if (!S) return 1; // memory allocation check

    for (int i = 0; i < Q; i++) {
        int type;
        scanf("%d", &type);

        if (type == 1) { // append
            char W[1000001]; // enough for constraints
            scanf("%s", W);
            push(S);
            if (strlen(S) + strlen(W) < MAX_LEN) {
                strcat(S, W);
            }
        } 
        else if (type == 2) { // delete
            int k;
            scanf("%d", &k);
            push(S);
            int len = strlen(S);
            if (k <= len) {
                S[len - k] = '\0';
            }
        } 
        else if (type == 3) { // print
            int k;
            scanf("%d", &k);
            if (k > 0 && k <= (int)strlen(S)) {
                printf("%c\n", S[k - 1]);
            }
        } 
        else if (type == 4) { // undo
            char *prev = pop();
            if (prev) {
                strcpy(S, prev);
                free(prev);
            }
        }
    }

    free(S);
    return 0;
}
