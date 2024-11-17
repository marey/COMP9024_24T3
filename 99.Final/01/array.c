#include <stdio.h>


void PrintArray(int *ptr, int n) {
    if (n > 0) {
        // 递归调用
        PrintArray(ptr + 1, n - 1);
        printf("%d ", *ptr);
    }
}

void Swap (int *pa, int *pb) {
    int tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

/*
    Bubble sort the n numbers pointed to by ptr.
    The elements are sorted in ascending order (from the least to the greatest).
 */
void BubbleSort(int *ptr, int n, int *count) {
    /*
        1. iMax represents the max value of i in a pass
              (in the following "if (ptr[i] > ptr[i+1])")

        2. (n-1) passes needed in Bubble Sort
     */
    
    for (int iMax = n - 2; iMax >= 0; iMax--) { // (n-1) passes
        
        // printf() is quite useful in observing the behavior of a program
        printf("............... iMax = %d ...............\n\n", iMax);
        PrintArray(ptr, iMax + 2);
        printf("\n\n");

        // i is in [0, iMax] in the current pass
        for (int i = 0; i <= iMax; i++) {
            if (ptr[i] > ptr[i+1]) {
                (*count) ++;
                Swap(ptr + i, ptr + i + 1);
                printf("After swapping ptr[%d] and ptr[%d]:\n", i, i+1);
                PrintArray(ptr, iMax + 2);
                printf("\n");
            }
        }       
    }
}

void BubbleSort2 (int *ptr, int n, int *count) {
    if (n > 1) {
        for (int i = 0; i <= n - 2; i++) {
            if (ptr[i] > ptr[i + 1]) {
                (*count) ++;
                Swap(ptr + i, ptr + i + 1);
            }
        }
        BubbleSort2(ptr, n - 1, count);
    }
}

int main(void) {

    int array1[3] = {30, 50, 20};
    int array2[4] = {30, 50, 20, 40};
    int count1 = 0, count2 = 0;
    BubbleSort(array1, 3, &count1);
    BubbleSort(array2, 4, &count2);
    printf("count1 %d, count2: %d \n", count1, count2);


    return 0;
}