#include <stdio.h>
#include <string.h>

int main() {
    char str[257];

    if (fgets(str, sizeof(str), stdin) != NULL) {
        int i = 0;
        for (; i < 256; i++) {
            if (str[i] == ' ' || str[i] == '\n') {
                continue;
            }
            if (str[i] == '.' || str[i] == '\0') {
                break;
            }
        }

        int size = i;
        char rev[size + 1];
        rev[size] = '\0';
        i--;

        for (; i >= 0; i--) {
            rev[size - 1 - i] = str[i];
        }

        printf("%s\n", rev);
    }

    return 0;
}
