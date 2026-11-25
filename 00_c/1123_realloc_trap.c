/* 1123_realloc_trap.c
 * 目标：同一个错误，两种写法；用 valgrind 抓出"正确写法不泄漏、错误写法泄漏 16 字节"
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    size_t huge = (size_t)-1;        /* SIZE_MAX，realloc 必定失败 */

    /* ---------- 正确写法：临时变量接 ---------- */
    int *p = malloc(4 * sizeof(int));
    if (!p) { perror("malloc p"); return 1; }
    for (int i = 0; i < 4; i++) p[i] = i + 1;
    printf("正确写法：原块 p = %p，内容 %d %d %d %d\n", (void *)p, p[0], p[1], p[2], p[3]);

    int *tmp = realloc(p, huge);
    if (tmp == NULL) {
        printf("realloc 失败（errno=%d %s）\n", errno, strerror(errno));
        printf("原指针 p = %p 仍有效，内容仍是 %d %d %d %d\n", (void *)p, p[0], p[1], p[2], p[3]);
    } else {
        p = tmp;
    }
    free(p); p = NULL;

    /* ---------- 错误写法：直接覆盖 ---------- */
    int *q = malloc(4 * sizeof(int));
    if (!q) { perror("malloc q"); return 1; }
    for (int i = 0; i < 4; i++) q[i] = i + 1;
    printf("\n错误写法：原块 q = %p\n", (void *)q);
    q = realloc(q, huge);            /* 失败 → q 变 NULL → 原地址丢失 */
    if (q == NULL) {
        printf("realloc 返回 NULL，q 已变成 NULL\n");
        printf("原来那块的地址没人记得了 → 泄漏 16 字节\n");
    }
    return 0;
}
