#include <stdio.h>
#include <string.h>
#include <ctype.h>

int is_vowel(char ch) {
    ch = tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}

int main() {
    char str[100];
    int left = 0, right;

    // Input
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; // remove newline

    right = strlen(str) - 1;

    // Two-pointer vowel swap
    while (left < right) {
        // Skip non-vowels from left
        while (left < right && !is_vowel(str[left])) {
            left++;
        }
        // Skip non-vowels from right
        while (left < right && !is_vowel(str[right])) {
            right--;
        }

        // Swap the vowels
        if (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;

            left++;
            right--;
        }
    }

    // Output
    printf("Modified string: %s\n", str);
    return 0;
}
