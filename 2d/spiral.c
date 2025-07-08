#include <stdio.h>
#include<stdlib.h>

void printSpiral(int **matrix, int rows, int cols) {
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;

    while (top <= bottom && left <= right) {
        // Step 1: Left to Right
        for (int i = left; i <= right; i++)
            printf("%d ", matrix[top][i]);
        top++;

        // Step 2: Top to Bottom
        for (int i = top; i <= bottom; i++)
            printf("%d ", matrix[i][right]);
        right--;

        // Step 3: Right to Left
        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                printf("%d ", matrix[bottom][i]);
            bottom--;
        }

        // Step 4: Bottom to Top
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                printf("%d ", matrix[i][left]);
            left++;
        }
    }
    printf("\n");
}

int main()
{
    int n, m;
    scanf("%d %d",&n,&m);

    int **matrix = (int **)malloc(n*sizeof(int *));  // rows;
    for(int i=0;i<n;i++)  // columns
    {
        matrix[i] = (int *)malloc(m* sizeof(int));
    }

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            scanf("%d",&matrix[i][j]);
    }

    printSpiral(matrix,n,m);

    for(int i=0;i<n;i++)
        free(matrix[i]);

    free(matrix);

    return 0;
}