/*#include <stdio.h>
#include <string.h>

int main() {
    char str[200];
    int visited[200] = {0};  // To mark counted characters

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    int len = strlen(str);

    printf("\nFrequencies:\n");
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ' || str[i] == '\n')  // Skip spaces/newline
            continue;

        if (visited[i] == 1)  // Already counted
            continue;

        int count = 1;
        for (int j = i + 1; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
                visited[j] = 1;
            }
        }
        printf("%c → %d times\n", str[i], count);
    }

    return 0;
} */
 
// Program to print the frequency of each character
#include <stdio.h>
#include <string.h>

int main() {
    char str[200];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    int len = strlen(str);

    printf("\nFrequencies:\n");
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

        if (str[i] != '\0')  // Only print if not already marked
            printf("%c → %d times\n", str[i], count);
    }

    return 0;
}

