#include <stdio.h>

int main(void) {
    int a[5];

    printf("sizeof(a)   = %zu\n", sizeof(a));      /* 数组总大小 */
    printf("sizeof(&a)  = %zu\n", sizeof(&a));     /* 指针自己多大 */
    printf("sizeof(*a)  = %zu\n", sizeof(*a));     /* a+1 走多远 */
    printf("sizeof(*&a) = %zu\n", sizeof(*&a));    /* &a+1 走多远 */

    return 0;
}
