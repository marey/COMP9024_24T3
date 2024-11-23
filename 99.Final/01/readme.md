# 期末真题

## Q1 真题

```c
#include <stdio.h>

int g(int m, int n) {
    if (n == 0) {
        return m;
    } else {
        return g(n, m % n)
    }
}

int main(void) {
    printf("%d\n", g(90,24));
}
```

The output of the above program is **\_\_\_\_Q1\_\_\_\_\_\_**

## Q2 真题

```c
#include <stdio.h>
#include <assert.h>

void f(int *arr, int n) {
    unsigned int maxVal = (1 << n);
    assert(n < (sizeof(maxVal) * 8));
    for (unsigned int curVal = 0; curVal < maxVal; curVal++) {
        printf("{ ");

        for (int i = 0; i < n ; i++) {
            if ((curVal & (1 << i)) != 0) {
                printf("%d", arr[i]);
            }
        }
        printf("}\n");
    }
}

int main(void) {
    int nums[] = {50, 60, 70};
    int n = sizeof(nums) / sizeof(nums[0]);
    f(nums, n);
    return 0;
}

```

The output of the above program is **\_\_\_\_Q2\_\_\_\_\_\_**

## Q3 真题

```c
#include <stdio.h>

int count1 = 0;
int count2 = 0;

void swap(int *pa, int *pb) {
    int temp;
    temp = *pa;
    *pa = *pb;
    *pb = temp;
}

void f(int *arr, int n, int left, int right) {
    count1++;

    if (left == right) {
        count2++;
        return;
    }
    for(int i = left; i <= right; i++) {
        swap(&arr[left], &arr[i]);
        f(arr, n,  left + 1, right);
        swap(&arr[left], &arr[i]);
    }
}

int main(void) {
    int nums[] = {10, 20, 30, 40, 50};
    int n = sizeof(nums) / sizeof(nums[0]);
    f(nums, n, 0, n -1);
    return 0;
}


```

After finishing the function call f(nums, n, 0, n-1), the value of the `count1` is **\_\_326\_\_**

After finishing the function call f(nums, n, 0, n-1), the value of the `count2` is **\_\_120\_\_**

## 29 真题

```c
#include <stdio.h>

int main(int argc, char **argv, char **env) {
    for (int i = 0; ______; i++) {
        printf("%s\n", env[i]);
    }
}

```

The program above outputs a list of all enviroment variables.

## 30 真题

```c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    srandom(time(null));

    long y = 0;
    for (int i = 0; i < 2024; i++) {
        long x = random();
        x %= 3;
        y|= (1 << x);
    }

    printf("%ld\n", y);
}

```

if the random function produces sufficiently rand values, the output of the above program is most likely to be **\_\_\_\_Q30\_\_\_\_**

答案最可能是 7
