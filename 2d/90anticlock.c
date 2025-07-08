#include <stdio.h>

/* Step 1: Transpose (swap rows with columns)
   Step 2: Reverse each column for 90° anticlockwise rotation
*/

void reverse(int n, int col, int arr[][n]) {
    int top = 0, bottom = n - 1;
    while (top < bottom) {
        int temp = arr[top][col];
        arr[top][col] = arr[bottom][col];
        arr[bottom][col] = temp;
        top++;
        bottom--;
    }
}

int main() {
    int n;
    printf("Enter size of the matrix: ");
    scanf("%d", &n);
    int arr[n][n];

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    printf("Original matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    // Step 1: Transpose rows with columns
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            arr[i][j] ^= arr[j][i];
            arr[j][i] ^= arr[i][j];
            arr[i][j] ^= arr[j][i];
        }
    }

    // Step 2: Reverse each column
    for (int i = 0; i < n; i++) {
        reverse(n, i, arr);
    }

    printf("Matrix after 90 degree anti-clockwise rotation:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    return 0;
}
