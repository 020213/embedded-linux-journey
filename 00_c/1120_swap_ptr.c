#include <stdio.h>

void swap_ptr(int *a, int *b)
{
    printf("  函数内 a、b 装的是: %p  %p\n", (void *)a, (void *)b);
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(void)
{
    int x = 10, y = 20;

    printf("调用前: x=%d  y=%d\n", x, y);
    printf("x、y 的地址: %p  %p\n", (void *)&x, (void *)&y);

    swap_ptr(&x, &y);

    printf("调用后: x=%d  y=%d   <-- 值变了\n", x, y);
    return 0;
}