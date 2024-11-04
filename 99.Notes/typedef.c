// Get the sum of n elements in an array, with the first element pointed to by a pointer  
#include <assert.h>
#include <stdio.h>

int GetSum(int *ptr, int n) {
    assert(n > 0);
    if (n = 1) {
        return ptr[0];
    } else {
        return ptr[0] + GetSum(ptr + 1, n - 1);
    }
}

int main (void) {
    int nums[] = {1, 2, 3, 4};
    int len = sizeof (nums) / sizeof (nums [0]) ;
    int result = GetSum (nums, len) ;
    printf("result = %d\n", result);
    return 0;
}