#include<stdio.h>

void rotate180_easy(int n, int a[][n])
{
    /* Step 1: reverse each row */
    for (int row = 0; row < n; row++) {
        int left = 0, right = n - 1;
        while (left < right) {
            int temp = a[row][left];
            a[row][left] = a[row][right];
            a[row][right] = temp;
            left++; 
            right--;
        }
    }

    /* Step 2: reverse each column */
    for (int col = 0; col < n; col++) {
        int top= 0, bottom = n - 1;
        while (top < bottom) {
            int temp = a[top][col];
            a[top][col] = a[bottom][col];
            a[bottom][col] = temp;
            top++; 
            bottom--;
        }
    }
}

int main()
{
    int n;
    printf("Enter n\n");
    scanf("%d",&n);
    int arr[n][n];
    printf("Enter array elements for %d matrix\n",n*n);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            scanf("%d",&arr[i][j]);
    }

    printf("Original Matrix\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
           printf("%d ",arr[i][j]);
        printf("\n");
    }

    rotate180_easy(n,arr);

    printf("Matrix after 180 degree rotation\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
           printf("%d ",arr[i][j]);
        printf("\n");
    }

    return 0;
}
