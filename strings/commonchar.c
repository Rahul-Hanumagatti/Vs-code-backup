//C program to find common characters between two strings:

#include <stdio.h>
#include <string.h>

int main() {
    char str1[] = "Write about Yourself";
    char str2[] = "Hello I am shakeel";

    printf("Common characters:\n");

    for (int i = 0; str1[i] != '\0'; i++) {
        for (int j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {         // if match found
                printf("%c\n", str1[i]);
                break;                        // avoid printing duplicates
            }
        }
    }

    return 0;
}
