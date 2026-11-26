/* 1125_mystring.c —— S1-1-3 手写 my_strlen / my_strcpy / my_strcmp / my_strcat */
#include <stdio.h>
#include <stddef.h>

size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p != '\0') {
        p++;
    }
    return (size_t)(p - s);
}

char *my_strcpy(char *dest, const char *src)
{
    char *d = dest;

    while ((*d++ = *src++) != '\0') {
        ;
    }
    return dest;
}

int my_strcmp(const char *s1, const char *s2)
{
    const unsigned char *p1 = (const unsigned char *)s1;
    const unsigned char *p2 = (const unsigned char *)s2;

    while (*p1 != '\0' && *p1 == *p2) {
        p1++;
        p2++;
    }
    return (int)(*p1 - *p2);
}

char *my_strcat(char *dest, const char *src)
{
    char *d = dest;

    while (*d != '\0') {
        d++;
    }
    while ((*d++ = *src++) != '\0') {
        ;
    }
    return dest;
}

static void show(const char *tag, const char *s)
{
    printf("  %-24s = \"%s\" (len=%zu)\n", tag, s, my_strlen(s));
}

int main(void)
{
    char buf[32];
    char small[8];

    printf("=== P1 基本正确性 ===\n");
    printf("  my_strlen(\"\")      = %zu\n", my_strlen(""));
    printf("  my_strlen(\"T-Box\") = %zu\n", my_strlen("T-Box"));
    printf("  my_strlen(\"CAN\")   = %zu\n", my_strlen("CAN"));

    my_strcpy(buf, "T-Box");
    show("my_strcpy -> buf", buf);
    printf("  链式返回值 = \"%s\"\n", my_strcpy(small, "CAN"));

    my_strcat(buf, "/CAN");
    show("my_strcat(buf,\"/CAN\")", buf);
    my_strcat(buf, "");
    show("my_strcat(buf,\"\")", buf);

    printf("  my_strcmp(\"abc\",\"abc\") = %d\n", my_strcmp("abc", "abc"));
    printf("  my_strcmp(\"abc\",\"abd\") = %d\n", my_strcmp("abc", "abd"));
    printf("  my_strcmp(\"abd\",\"abc\") = %d\n", my_strcmp("abd", "abc"));
    printf("  my_strcmp(\"ab\",\"abc\")  = %d\n", my_strcmp("ab", "abc"));
    printf("  my_strcmp(\"abc\",\"ab\")  = %d\n", my_strcmp("abc", "ab"));

    printf("\n=== P2 size_t 回绕陷阱 ===\n");
    if (my_strlen("abc") - my_strlen("abcd") > 0) {
        printf("  [!] 3 - 4 竟然 > 0 ：size_t 无符号，减法回绕成 18446744073709551615\n");
    } else {
        printf("  未回绕\n");
    }
    printf("  先转 int 再减 = %d\n",
           (int)my_strlen("abc") - (int)my_strlen("abcd"));

    printf("\n=== P3 有符号 char 比较陷阱 ===\n");
    {
        const char hi[2] = { (char)0x80, '\0' };
        const char lo[2] = { 'a', '\0' };

        printf("  正确实现 my_strcmp(0x80, 'a') = %d\n", my_strcmp(hi, lo));
        printf("  若直接用有符号 char 裸减     = %d\n",
               (int)(char)0x80 - (int)'a');
    }

    printf("\n=== P4 空串与单字符边界 ===\n");
    printf("  my_strcmp(\"\",\"\")   = %d\n", my_strcmp("", ""));
    printf("  my_strcmp(\"\",\"a\")  = %d\n", my_strcmp("", "a"));
    printf("  my_strcmp(\"a\",\"\")  = %d\n", my_strcmp("a", ""));
    my_strcpy(small, "");
    show("my_strcpy(small,\"\")", small);

    return 0;
}
