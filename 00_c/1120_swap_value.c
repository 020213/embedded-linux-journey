#include <stdio.h>

void swap_value(int a, int b)
{
    printf("  函数内收到副本的地址: &a=%p  &b=%p\n", (void *)&a, (void *)&b);
    int tmp = a;
    a = b;
    b = tmp;
    printf("  函数内交换后: a=%d  b=%d\n", a, b);
}

int main(void)
{
    int x = 10, y = 20;
    printf("调用前: x=%d  y=%d\n", x, y);
    printf("main 里变量的地址: &x=%p  &y=%p\n", (void *)&x, (void *)&y);

    swap_value(x, y);

    printf("调用后: x=%d  y=%d   <-- 纹丝不动\n", x, y);
    return 0;
}
