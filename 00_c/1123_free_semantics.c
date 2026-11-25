/* 1123_free_semantics.c
 * 目标：实测 free 到底还了多少给 OS —— 小块走 brk 不还，大块走 mmap 真还
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static long vmrss_kb(void)
{
    FILE *fp = fopen("/proc/self/status", "r");
    if (!fp) return -1;
    char line[256];
    long kb = -1;
    while (fgets(line, sizeof line, fp)) {
        if (strncmp(line, "VmRSS:", 6) == 0) { sscanf(line + 6, "%ld", &kb); break; }
    }
    fclose(fp);
    return kb;
}

int main(void)
{
    /* ---------- 小块 100KB < 128KB，走 brk ---------- */
    const size_t SMALL = 100 * 1024;
    printf("=== 小块 100KB（走 brk）===\n");
    printf("初始     VmRSS = %ld KB\n", vmrss_kb());
    unsigned char *s = malloc(SMALL);
    if (!s) { perror("malloc small"); return 1; }
    memset(s, 1, SMALL);
    printf("写满后   VmRSS = %ld KB\n", vmrss_kb());
    free(s); s = NULL;
    printf("free 后  VmRSS = %ld KB\n\n", vmrss_kb());

    /* ---------- 大块 64MB > 128KB，走 mmap ---------- */
    const size_t BIG = 64UL * 1024 * 1024;
    printf("=== 大块 64MB（走 mmap）===\n");
    printf("申请前   VmRSS = %ld KB\n", vmrss_kb());
    unsigned char *b = malloc(BIG);
    if (!b) { perror("malloc big"); return 1; }
    memset(b, 1, BIG);
    printf("写满后   VmRSS = %ld KB\n", vmrss_kb());
    free(b); b = NULL;
    printf("free 后  VmRSS = %ld KB\n", vmrss_kb());
    return 0;
}
