#include <stdio.h>

int main(void) {
    char a[] = "abc";        /* 栈上拷贝，可写 */
    char *p  = "abc";        /* p 指向只读常量区 */

    printf("sizeof(a) = %zu\n", sizeof(a));   /* 4，含结尾 '\0' */
    printf("sizeof(p) = %zu\n", sizeof(p));   /* 8 */

    a[0] = 'X';
    printf("a = %s\n", a);                    /* Xbc */

    /* 下面这行取消注释后，编译不报错，运行时段错误 */
    p[0] = 'X';

    printf("p = %s\n", p);

    return 0;
}
