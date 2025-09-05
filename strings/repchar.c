// Program to print the repeating characters in string

#include <stdio.h>
#include <string.h>

int main() {
    char str[200];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    int len = strlen(str);

    printf("\nRepeating characters:\n");
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\0')
            continue;

        int count = 1;
        for (int j = i + 1; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
                str[j] = '\0';   // Mark as counted
            }
        }

        if (count > 1 && str[i] != '\0')
            printf("%c → %d times\n", str[i], count);
    }

    return 0;
}
