#include <stdio.h>
#include "linked-list.h"
int main(void)
{
    conscell *list = NULL; // an empty list
    int a = 101, b = -45, c = 1000, d = 12;
    list = ll_push(list, &a);
    list = ll_push(list, &b);
    list = ll_push(list, &c);
    list = ll_push(list, &d);
    printf("the original linked list:\n");
    for (conscell *p = list; p != NULL; p = p->next)
        printf("%d ", *(int *)p->data);
    list = ll_reverse(list);
    printf("\nthe reversed linked list:\n");
    for (conscell *p = list; p != NULL; p = p->next)
        printf("%d ", *(int *)p->data);
    putchar('\n');
    return 0;
}