#include <stdio.h>
#include <string.h>

int main() {
    char str[200];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    int len = strlen(str);
    int maxCount = 0;
    char maxChar = '\0';

    for (int i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\0')
            continue;

        int count = 1;
        for (int j = i + 1; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
                str[j] = '\0';  // Mark as visited
            }
        }

        if (count > maxCount && str[i] != '\0') {
            maxCount = count;
            maxChar = str[i];
        }
    }

    if (maxChar != '\0')
        printf("Most repeated character: %c → %d times\n", maxChar, maxCount);
    else
        printf("No repeated characters found.\n");

    return 0;
}
