#include <stdio.h>
#include "linked-list.h"

int catch_the_odds(void *aa) // correct form
{
    int a = *(int *)aa;
    return a%2;
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
    conscell *removed = NULL;
    list = ll_filter(list, catch_the_odds, &removed);
    printf("the list after removing odds:\n");
    for (conscell *p = list; p != NULL; p = p->next)
        printf("%d ", *(int *)p->data);
    printf("\nthe removed items:\n");
    for (conscell *p = removed; p != NULL; p = p->next)
        printf("%d ", *(int *)p->data);
    putchar('\n');
    ll_free(list);
    printf("linked list memory freed\n");
    ll_free(removed);
    return 0;
}