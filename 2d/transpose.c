// Program to transpose matrix , rows to columns and columns to rows

#include<stdio.h>

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n][m];

    // Read the matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            scanf("%d", &arr[i][j]);
    }

    // Print transpose
    // for(int j = 0; j < m; j++) {
    //     for(int i = 0; i < n; i++)
    //         printf("%d ", arr[i][j]);
    //     printf("\n");
    // }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++)
            printf("%d ", arr[j][i]);
        printf("\n");
    }


    return 0;
}
