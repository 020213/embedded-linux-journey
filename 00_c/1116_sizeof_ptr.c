#include <stdio.h>

int main(void) {
    char   *pc = NULL;
    int    *pi = NULL;
    double *pd = NULL;

    printf("%-8s %-12s %-12s\n", "类型", "sizeof(ptr)", "sizeof(*ptr)");
    printf("%-8s %-12zu %-12zu\n", "char*",   sizeof(pc), sizeof(*pc));
    printf("%-8s %-12zu %-12zu\n", "int*",    sizeof(pi), sizeof(*pi));
    printf("%-8s %-12zu %-12zu\n", "double*", sizeof(pd), sizeof(*pd));
    printf("%-8s %-12zu %-12zu\n", "void*",   sizeof(void *), sizeof(void));

    return 0;
}
