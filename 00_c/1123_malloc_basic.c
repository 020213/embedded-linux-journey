/* 1123_malloc_basic.c
 * 目标：① 连续两块的间隔  ② malloc 不清零铁证  ③ calloc 清零对比
 *       ④ 句柄在栈/本体在堆  ⑤ malloc(0)
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* ---------- 步骤 1：连续两块的间隔（此时 tcache 为空，最稳） ---------- */
    printf("=== 步骤 1：连续两块的间隔 ===\n");
    int *i1 = malloc(16);
    int *i2 = malloc(16);
    if (!i1 || !i2) { perror("malloc i"); return 1; }
    printf("i1      = %p\n", (void *)i1);
    printf("i2      = %p\n", (void *)i2);
    printf("i2 - i1 = %ld 字节（请求 16）\n", (long)((char *)i2 - (char *)i1));
    printf("判据：间隔 > 16 → 每块带 chunk header + 对齐；不要背具体数字\n\n");
    free(i1); free(i2); i1 = i2 = NULL;

    /* ---------- 步骤 2：malloc 不清零的铁证 ---------- */
    printf("=== 步骤 2：malloc 不清零 ===\n");
    int *c = malloc(4 * sizeof(int));
    if (!c) { perror("malloc c"); return 1; }
    c[0] = 111; c[1] = 222; c[2] = 333; c[3] = 444;
    printf("c       = %p   写入 111 222 333 444，随即 free\n", (void *)c);
    free(c); c = NULL;

    int *d = malloc(4 * sizeof(int));   /* 同尺寸，大概率原样拿回刚释放的块 */
    if (!d) { perror("malloc d"); return 1; }
    printf("d       = %p\n", (void *)d);
    printf("d[0..3] = %d %d %d %d\n", d[0], d[1], d[2], d[3]);
    printf("判据：若 d 地址与 c 相同且内容仍是 111 222 333 444 → malloc 不清零\n\n");
    free(d); d = NULL;

    /* ---------- 步骤 3：calloc 清零 ---------- */
    printf("=== 步骤 3：calloc 清零 ===\n");
    int *e = calloc(4, sizeof(int));
    if (!e) { perror("calloc e"); return 1; }
    printf("e       = %p\n", (void *)e);
    printf("e[0..3] = %d %d %d %d\n", e[0], e[1], e[2], e[3]);
    printf("判据：同一块，malloc 出来是旧值，calloc 出来全 0\n\n");
    free(e); e = NULL;

    /* ---------- 步骤 4：句柄在栈，本体在堆 ---------- */
    printf("=== 步骤 4：句柄在哪，本体在哪 ===\n");
    int  local = 1;
    int *h = malloc(4 * sizeof(int));
    if (!h) { perror("malloc h"); return 1; }
    printf("&local  = %p   栈：local 这个变量自己\n", (void *)&local);
    printf("&h      = %p   栈：指针变量 h 自己\n", (void *)&h);
    printf("h       = %p   堆：h 里存的值（指向堆）\n", (void *)h);
    printf("判据：&h 与 h 差一个量级；&h 与 &local 同区\n\n");
    free(h); h = NULL;

    /* ---------- 步骤 5：malloc(0) ---------- */
    printf("=== 步骤 5：malloc(0) ===\n");
    void *z = malloc(0);
    printf("malloc(0) = %p   合法、可 free、不可解引用\n", z);
    free(z);

    return 0;
}
