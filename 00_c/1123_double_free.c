/* 1123_double_free.c
 * 警告：这个程序会崩，崩就是目的。看清报错信息即可
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p = malloc(4 * sizeof(int));
    if (!p) { perror("malloc"); return 1; }
    p[0] = 1;

    printf("第一次 free(%p)\n", (void *)p);
    fflush(stdout);
    free(p);

    printf("free 之后 p 仍然是 %p —— 悬空指针，值没变\n", (void *)p);
    fflush(stdout);

    printf("第二次 free(%p) —— 同一地址再 free\n", (void *)p);
    fflush(stdout);
    free(p);            /* glibc 的 tcache 会检测到 double free，直接 abort */

    printf("这行不会执行\n");
    return 0;
}
