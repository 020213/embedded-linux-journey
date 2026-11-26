/* 1125_overflow.c —— P5：my_strcpy 不检查缓冲区大小，越界是调用者的锅 */
#include <stdio.h>
#include <stdlib.h>

char *my_strcpy(char *dest, const char *src)
{
    char *d = dest;

    while ((*d++ = *src++) != '\0') {
        ;
    }
    return dest;
}

int main(void)
{
    char *h = malloc(4);          /* 只有 4 字节堆放区 */

    if (h == NULL) {
        return 1;
    }
    printf("malloc(4) 成功，准备拷入 \"T-Box/CAN\"（10 字节 + 1 个 '\\0'）\n");
    fflush(stdout);

    my_strcpy(h, "T-Box/CAN");    /* 写 11 字节进 4 字节块 → 堆越界 */

    printf("拷完了，h = %s\n", h);
    free(h);
    printf("free 也过了，进程退出码正常\n");
    return 0;
}
