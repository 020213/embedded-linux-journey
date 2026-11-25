#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *msg = malloc(32);
    if (!msg)
    {
        perror("malloc msg");
        return 1;
    }
    strcpy(msg, "T-Box: CAN frame received");
    printf("[before] %s\n", msg);
    free(msg);
    /* msg = NULL;    ← 故意漏掉这行（S1-1-1 铁律③） */

    /* ↓↓↓ 以下全是悬空使用 ↓↓↓ */
    printf("[after ] strlen = %zu\n", strlen(msg));
    printf("[after ] %s\n", msg);

    return 0;
}
