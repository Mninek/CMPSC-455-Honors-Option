#include <stdio.h>
#include "linked-list.h"
int cmp1(const void *aa, const void *bb, void *pp) // correct form
{
    int a = *(int *)aa;
    int b = *(int *)bb;
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

int cmp2(const void *aa, const void *bb, void *pp) // correct form
{
    int a = *(int *)aa;
    int b = *(int *)bb;
    if (a > b)
        return -1;
    else if (a < b)
        return 1;
    else
        return 0;
}

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
    putchar('\n');
    printf("the linked list sorted in ascending order:\n");
    list = ll_sort(list, cmp1, NULL);
    for (conscell *p = list; p != NULL; p = p->next)
        printf("%d ", *(int *)p->data);
    putchar('\n');
    printf("the linked list sorted in descending order:\n");
    list = ll_sort(list, cmp2, NULL);
    for (conscell *p = list; p != NULL; p = p->next)
        printf("%d ", *(int *)p->data);
    putchar('\n');

    ll_free(list);
    printf("linked list memory freed\n");
    return 0;
}