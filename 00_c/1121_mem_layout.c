#include<stdio.h>
#include<stdlib.h>

int g_init = 42;
int g_uninit;
const int g_const = 7;

int main(void)
{
    int local = 1;
    static int s_local;
    int *heap = malloc(16);
    char *s = "abc";

    printf("main      %p   .text\n",  (void *)main);
    printf("g_const   %p   .rodata\n", (void *)&g_const);
    printf("s         %p   .rodata\n", (void *)s);
    printf("g_init    %p   .data\n",   (void *)&g_init);
    printf("g_uninit  %p   .bss\n",    (void *)&g_uninit);
    printf("s_local   %p   .bss\n",    (void *)&s_local);
    printf("heap      %p   堆\n",      (void *)heap);
    printf("local     %p   栈\n",      (void *)&local);

    free(heap);
    return 0;
}
