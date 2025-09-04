/*
Write a program to shift each letter in a string by one position in the alphabet.
Example:
Input: yogitha
Output: zphjuiz

*/

#include <stdio.h>

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%[^\n]", str);   // read full line with spaces

    int i = 0;
    while (str[i] != '\0') 
    {
        if (str[i] >= 'a' && str[i] <= 'z') 
        {   // lowercase
            if (str[i] == 'z')
                str[i] = 'a';
            else
                str[i] = str[i] + 1;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z') 
        { // uppercase
            if (str[i] == 'Z')
                str[i] = 'A';
            else
                str[i] = str[i] + 1;
        }
        // else → leave other chars as they are
        i++;
    }

    printf("Output: %s\n", str);
    return 0;
}
