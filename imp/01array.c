
// WAP to arranging the arrays {1110110} -> {1111100}.
#include <stdio.h>

int main() {
    int size=0;
    scanf("%d",&size);
    int arr[size];// = {1,1,1,0,1,1,0};

    for(int i=0;i<size;i++)
        scanf("%d",&arr[i]);

    //int n = sizeof(arr)/sizeof(arr[0]);
    int left = 0, right = size- 1;

    while (left < right) {
        // If left is 1, move forward
        if (arr[left] == 1) {
            left++;
        }
        // If right is 0, move backward
        else if (arr[right] == 0) {
            right--;
        }
        // Swap if left is 0 and right is 1
        else {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
    }

    // Print result
    printf("Arranged array: ");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}

#include <stdio.h>

int main() {
    int arr[] = {1,1,1,0,1,1,0};
    int n = sizeof(arr)/sizeof(arr[0]);
    int i, count = 0;

    // Count number of 1's
    for(i = 0; i < n; i++) {
        if(arr[i] == 1)
            count++;
    }

    // Fill array: first 'count' ones, then zeros
    for(i = 0; i < n; i++) {
        if(i < count)
            arr[i] = 1;
        else
            arr[i] = 0;
    }

    // Print result
    printf("Arranged array: ");
    for(i = 0; i < n; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");

    return 0;
}

