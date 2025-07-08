#include <stdio.h>
#include <stdlib.h>

int main() {
    int rowsA, colsA, rowsB, colsB;
    int i, j, k;

    printf("Enter number of rows for Matrix A: ");
    scanf("%d", &rowsA);
    printf("Enter number of columns for Matrix A: ");
    scanf("%d", &colsA);

    // Dynamically allocate Matrix A
    int **A = (int **)malloc(rowsA * sizeof(int *));
    for (i = 0; i < rowsA; i++)
        A[i] = (int *)malloc(colsA * sizeof(int));

    printf("Enter values for %d x %d matrix A:\n", rowsA, colsA);
    for (i = 0; i < rowsA; i++)
        for (j = 0; j < colsA; j++)
            scanf("%d", &A[i][j]);

    printf("Enter number of rows for Matrix B: ");
    scanf("%d", &rowsB);
    printf("Enter number of columns for Matrix B: ");
    scanf("%d", &colsB);

    // Matrix multiplication is not possible
    if (colsA != rowsB) {
        printf("Matrix multiplication is not possible.\n");
        return 0;
    }

    // Dynamically allocate Matrix B
    int **B = (int **)malloc(rowsB * sizeof(int *));
    for (i = 0; i < rowsB; i++)
        B[i] = (int *)malloc(colsB * sizeof(int));

    printf("Enter values for %d x %d matrix B:\n", rowsB, colsB);
    for (i = 0; i < rowsB; i++)
        for (j = 0; j < colsB; j++)
            scanf("%d", &B[i][j]);

    // Dynamically allocate Result Matrix R
    int **R = (int **)malloc(rowsA * sizeof(int *));
    for (i = 0; i < rowsA; i++)
        R[i] = (int *)malloc(colsB * sizeof(int));

    // Matrix multiplication
    for(int i=0;i<rowsA;i++)
    {
        for(int j=0;j<colsB;j++)
        {
            R[i][j]=0;
            for(int k=0;k<colsA;k++)
            {
                R[i][j]+= A[i][k] * B[k][j];
            }
        }
    }

    // Print Result
    printf("Product of two matrix :\n");
    for (i = 0; i < rowsA; i++) {
        for (j = 0; j < colsB; j++)
            printf("%d\t", R[i][j]);
        printf("\n");
    }

    // Free memory
    for (i = 0; i < rowsA; i++) free(A[i]);
    for (i = 0; i < rowsB; i++) free(B[i]);
    for (i = 0; i < rowsA; i++) free(R[i]);
    free(A); free(B); free(R);

    return 0;
}
