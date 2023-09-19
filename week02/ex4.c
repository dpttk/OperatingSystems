#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_SIZE 256


int count(const char *str, char target) {
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] == target || (str[i] >= 'a' && str[i] <= 'z' && str[i] - 32 == target)) ||
            (str[i] >= 'A' && str[i] <= 'Z' && str[i] + 32 == target)) {
            count++;
        }
    }
    return count;
}


void countAll(const char *str) {
    for (char c = 'a'; c <= 'z'; c++) {
        int charCount = count(str, c);
        if (charCount > 0) {
            printf("%c:%d, ", c, charCount);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_string>\n", argv[0]);
        return 1;
    }

    char inputString[MAX_STRING_SIZE];
    snprintf(inputString, sizeof(inputString), "%s", argv[1]);

    printf("Input: %s\n", inputString);
    countAll(inputString);

    return 0;
}

