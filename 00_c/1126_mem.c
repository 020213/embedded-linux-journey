/* 1126_mem.c —— S1-1-4 手写 my_memcpy / my_memmove / my_memset */
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

struct tbox_cfg {
    int  id;
    char name[8];
    int  flag;
};

int main(void)
{
    printf("=== P1 memcpy 基本正确性（非重叠）===\n");
    {
        char src[] = "T-Box";
        char dst[16];
        char *r;

        my_memset(dst, 0xAA, sizeof(dst));
        r = (char *)my_memcpy(dst, src, sizeof(src));
        printf("  拷字符串   dst = \"%s\"\n", dst);
        printf("  返回值即 dest 本身   r == dst ? %s\n", (r == dst) ? "yes" : "no");

        int bin[4]      = {0x11223344, 0x55667788, 0x99AABBCC, 0xDDEEFF00};
        int bin_copy[4] = {0};
        my_memcpy(bin_copy, bin, sizeof(bin));
        printf("  拷二进制   %08x %08x %08x %08x\n",
               (unsigned)bin_copy[0], (unsigned)bin_copy[1],
               (unsigned)bin_copy[2], (unsigned)bin_copy[3]);
        printf("  与 strcpy 的区别：0x00 字节照样拷，遇 0 不停\n");
    }

    printf("\n=== P2 重叠场景：memcpy 坏 / memmove 对 ===\n");
    {
        char b1[16] = "ABCDEFGH";
        char b2[16] = "ABCDEFGH";
        char b3[16] = "ABCDEFGH";
        char b4[16] = "ABCDEFGH";

        my_memcpy (b1 + 2, b1, 8);
        my_memmove(b2 + 2, b2, 8);
        my_memcpy (b3, b3 + 2, 8);
        my_memmove(b4, b4 + 2, 8);

        printf("  原串            = \"ABCDEFGH\"\n");
        printf("  memcpy (d>s)    = \"%s\"   <- 前向拷，源被自己覆盖\n", b1);
        printf("  memmove(d>s)    = \"%s\" <- 后向拷，结果正确\n", b2);
        printf("  memcpy (d<s)    = \"%s\"       <- 前向安全，碰巧对\n", b3);
        printf("  memmove(d<s)    = \"%s\"       <- 前向，同样对\n", b4);
    }

    printf("\n=== P3 memset 低 8 位陷阱 ===\n");
    {
        int arr[4] = {0, 0, 0, 0};

        my_memset(arr, 1, sizeof(arr));
        printf("  my_memset(arr, 1, sizeof(arr)) 后：\n");
        printf("    arr[0] = %d  = 0x%08X\n", arr[0], (unsigned)arr[0]);
        printf("    本意是每个 int 都等于 1，实际拿到 0x01010101\n");
        printf("  正确写法：用循环赋值，而不是 memset\n");
    }

    printf("\n=== P4 memset 返回值 / n=0 / 填充字符 ===\n");
    {
        char m[8];
        char keep[8] = "ABC";
        char *r;

        r = (char *)my_memset(m, 'X', 5);
        m[5] = '\0';
        printf("  memset(m,'X',5)  = \"%s\"  链式返回 == m ? %s\n",
               m, (r == m) ? "yes" : "no");

        my_memset(keep, 'Z', 0);
        printf("  memset(keep,'Z',0) = \"%s\"   n=0 一个字节都不动\n", keep);

        my_memset(keep + 3, '!', 2);
        printf("  memset(keep+3,'!',2) = \"%s\"\n", keep);
    }

    printf("\n=== P5 sizeof 陷阱 ===\n");
    {
        struct tbox_cfg cfg;
        struct tbox_cfg *p = &cfg;

        printf("  sizeof(struct tbox_cfg) = %zu   <- 要清这么多\n", sizeof(struct tbox_cfg));
        printf("  sizeof(p)               = %zu   <- 只是指针大小，清这个等于只清 8 字节\n", sizeof(p));
        printf("  sizeof(*p)              = %zu   <- 对\n", sizeof(*p));

        p->id   = 0x1234;
        p->flag = 0x5678;
        my_memset(p, 0, sizeof(*p));
        printf("  清零后 id=0x%X flag=0x%X\n", (unsigned)p->id, (unsigned)p->flag);
    }

    return 0;
}
