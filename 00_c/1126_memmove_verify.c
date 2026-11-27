/* 1126_memmove_verify.c —— 与 libc 对拍：my_memcpy / my_memmove / my_memset */
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

void *my_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    while (n-- > 0) {
        *d++ = *s++;
    }
    return dest;
}

void *my_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;

    if (d < s) {
        while (n-- > 0) {
            *d++ = *s++;
        }
    } else if (d > s) {
        d += n;
        s += n;
        while (n-- > 0) {
            *--d = *--s;
        }
    }
    return dest;
}

void *my_memset(void *s, int c, size_t n)
{
    unsigned char *p = (unsigned char *)s;

    while (n-- > 0) {
        *p++ = (unsigned char)c;
    }
    return s;
}

#define BUF    64
#define ROUNDS 20000

static unsigned int seed = 20261126u;
static unsigned int next_rand(void)
{
    seed = seed * 1103515245u + 12345u;
    return (seed >> 16) & 0x7FFF;
}

int main(void)
{
    unsigned char a[BUF], b[BUF];
    int i, bad_memmove = 0, bad_memcpy = 0, bad_memset = 0;
    int overlap_memmove = 0, nonoverlap_memcpy = 0;

    /* 1) my_memmove vs memmove —— 允许重叠 */
    for (i = 0; i < ROUNDS; i++) {
        size_t d_off = next_rand() % BUF;
        size_t s_off = next_rand() % BUF;
        size_t maxn  = BUF - (d_off > s_off ? d_off : s_off);
        size_t n     = (maxn > 0) ? (next_rand() % maxn) : 0;
        int k;

        for (k = 0; k < BUF; k++) {
            a[k] = b[k] = (unsigned char)(next_rand() & 0xFF);
        }

        memmove   (a + d_off, a + s_off, n);
        my_memmove(b + d_off, b + s_off, n);

        if (memcmp(a, b, BUF) != 0) {
            bad_memmove++;
        }
        if (d_off != s_off && n > 0) {
            overlap_memmove++;
        }
    }

    /* 2) my_memcpy vs memcpy —— 只测不重叠区间 */
    for (i = 0; i < ROUNDS; i++) {
        size_t d_off = next_rand() % (BUF / 2);
        size_t n     = 1 + (next_rand() % 16);
        size_t s_off = d_off + n + 1;   /* 严格确保不重叠 */
        int k;

        if (s_off + n > BUF) {
            continue;
        }
        for (k = 0; k < BUF; k++) {
            a[k] = b[k] = (unsigned char)(next_rand() & 0xFF);
        }

        memcpy   (a + d_off, a + s_off, n);
        my_memcpy(b + d_off, b + s_off, n);

        if (memcmp(a, b, BUF) != 0) {
            bad_memcpy++;
        }
        nonoverlap_memcpy++;
    }

    /* 3) my_memset vs memset —— 覆盖所有 256 种填充值 */
    for (i = 0; i < 256; i++) {
        size_t n = (size_t)(next_rand() % (BUF + 1));
        int k;

        for (k = 0; k < BUF; k++) {
            a[k] = b[k] = (unsigned char)(next_rand() & 0xFF);
        }

        memset   (a, i, n);
        my_memset(b, i, n);

        if (memcmp(a, b, BUF) != 0) {
            bad_memset++;
        }
    }

    printf("=== 对拍结果（每项 %d 轮）===\n", ROUNDS);
    printf("  my_memmove vs memmove : 不一致 %d 轮（其中真实重叠 %d 轮）\n",
           bad_memmove, overlap_memmove);
    printf("  my_memcpy  vs memcpy  : 不一致 %d 轮（非重叠 %d 轮）\n",
           bad_memcpy, nonoverlap_memcpy);
    printf("  my_memset  vs memset  : 不一致 %d 轮（256 种填充值）\n", bad_memset);
    printf("  结论：%s\n",
           (bad_memmove == 0 && bad_memcpy == 0 && bad_memset == 0)
               ? "全部一致，实现与 libc 行为等价" : "存在差异，需排查");
    return 0;
}
