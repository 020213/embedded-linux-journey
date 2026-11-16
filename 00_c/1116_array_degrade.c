#include <stdio.h>

void f(int arr[5])                      /* 方括号里的 5 会被编译器直接忽略 */
{
    printf("函数内 sizeof(arr) = %zu\n", sizeof(arr));   /* 8，已退化为指针 */
    arr[0] = 100;                        /* 内容能改，指向同一块内存 */
}

void g(int *arr, int n)
{
    printf("函数内 sizeof(arr) = %zu，传入的 n = %d\n", sizeof(arr), n);
}

int main(void)
{
    int a[5] = {1, 2, 3, 4, 5};

    printf("main 内 sizeof(a)   = %zu\n", sizeof(a));    /* 20 */

    f(a);
    g(a, 5);

    printf("a[0] = %d\n", a[0]);         /* 100，证明改的是同一块内存 */

    return 0;
}
