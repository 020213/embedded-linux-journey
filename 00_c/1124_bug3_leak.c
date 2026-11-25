/* 1124_bug3_leak.c —— 内存泄漏：提前 return 漏了 free */
#include <stdio.h>
#include <stdlib.h>

struct frame {
    int  id;
    char payload[56];       /* 模拟一帧数据 */
};

static void handle(int n)
{
    struct frame *f = malloc(sizeof *f);
    if (f == NULL) {
        return;
    }

    f->id = n;

    if (n % 3 == 0) {
        return;             /* ← 泄漏点：这条路径没 free */
    }

    free(f);
}

int main(void)
{
    for (int i = 0; i < 300; i++) {
        handle(i);
    }
    printf("done\n");
    return 0;
}
