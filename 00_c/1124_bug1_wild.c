/* 1124_bug1_wild.c —— 造一个野指针：指针里是个从来没有合法过的地址 */
#include <stdio.h>
#include <stdlib.h>

struct node {
    int          val;
    struct node *next;
};

int main(void)
{
    /* 现实中这个 0x1 不是你手写的，而是：
       - 未初始化栈上的残值
       - 数组越界算出来的偏移
       - 被截断/强转过的地址
       效果完全一样：编译零警告，运行必崩。 */
    struct node *p = (struct node *)0x1;
    struct node *head = NULL; 

    p->val  = 100;          /* ← 崩在这：往 0x1 写 */
    p->next = head;
    head    = p;

    printf("head->val = %d\n", head->val);
    free(head);
    return 0;
}
