#include <stdio.h>

/* 版本 A：一级指针，只能改值，换不了 p1/p2 本身 */
void swap_ptr(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* 版本 B：二级指针，能改 p1/p2 本身 */
void swap_pv(int **pa, int **pb)
{
    int *tmp = *pa;      /* *pa 就是 main 里的 p1 */
    *pa = *pb;           /* 把 p2 的值写进 p1 那个格子 */
    *pb = tmp;
}

int main(void)
{
    int x = 10, y = 20;

    /* ---- 情形一：用一级指针，只改值 ---- */
    int *p1 = &x, *p2 = &y;
    printf("=== 情形一 swap_ptr(p1, p2) ===\n");
    printf("交换前: p1->%p(%d)  p2->%p(%d)\n", (void *)p1, *p1, (void *)p2, *p2);

    swap_ptr(p1, p2);

    printf("交换后: p1->%p(%d)  p2->%p(%d)\n", (void *)p1, *p1, (void *)p2, *p2);
    printf("结论: p1、p2 的指向没变，变的是 x、y 的内容\n\n");

    /* ---- 情形二：用二级指针，换指针本身 ---- */
    p1 = &x;  p2 = &y;   /* 先复位 */
    printf("=== 情形二 swap_pv(&p1, &p2) ===\n");
    printf("交换前: p1->%p(%d)  p2->%p(%d)\n", (void *)p1, *p1, (void *)p2, *p2);

    swap_pv(&p1, &p2);

    printf("交换后: p1->%p(%d)  p2->%p(%d)\n", (void *)p1, *p1, (void *)p2, *p2);
    printf("结论: p1 现在指向 y，p2 指向 x，指针本身被改了\n\n");

    /* ---- 情形三：三级层级速查 ---- */
    printf("=== 三级层级速查 ===\n");
    printf("x        = %d\n", x);
    printf("*p1      = %d\n", *p1);
    printf("&x       = %p\n", (void *)&x);
    printf("p1       = %p\n", (void *)p1);
    printf("&p1      = %p\n", (void *)&p1);

    int **pp = &p1;
    printf("\npp       = %p   (等于 &p1)\n", (void *)pp);
    printf("*pp      = %p   (等于 p1)\n", (void *)*pp);
    printf("**pp     = %d   (等于 *p1 = %d)\n", **pp, *p1);
    printf("\nsizeof(p1)   = %zu\n", sizeof(p1));      /* 8 */
    printf("sizeof(pp)   = %zu\n", sizeof(pp));        /* 8 */
    printf("sizeof(*pp)  = %zu\n", sizeof(*pp));       /* 8，*pp 是 int* */
    printf("sizeof(**pp) = %zu\n", sizeof(**pp));      /* 4，**pp 是 int */

    return 0;
}
