#include <stdio.h>

int main(void) {
    int a[5];

    printf("a          = %p\n", (void *)a);
    printf("&a         = %p\n", (void *)&a);

    printf("a  +1 偏移 = %td 字节\n", (char *)(a + 1)  - (char *)a);
    printf("&a +1 偏移 = %td 字节\n", (char *)(&a + 1) - (char *)&a);

    return 0;
}
