#include <stdio.h>

/* Step 1: Transpose (swap rows with columns)
   Step 2: Reverse each row (for 90° clockwise rotation)
*/

void reverse(int n, int row, int arr[][n]) {
    int left = 0, right = n - 1;
    while (left < right) {
        int temp = arr[row][left];
        arr[row][left] = arr[row][right];
        arr[row][right] = temp;

        left++;
        right--;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n][n];

    // Read matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &arr[i][j]);

    printf("Original matrix\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }

    // Step 1: Transpose
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            arr[i][j] ^= arr[j][i];
            arr[j][i] ^= arr[i][j];
            arr[i][j] ^= arr[j][i];
        }
    }

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++) {
        reverse(n, i, arr);
    }

    // Print result
    printf("Matrix after 90 degree clockwise rotation:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }


    return 0;
}
