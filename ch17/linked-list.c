#include "linked-list.h"
#include "xmalloc.h"

conscell *ll_push(conscell *list, void *data)
{
    conscell *new = xmalloc(sizeof *new);
    new->data = data;
    new->next = list;
    return new;
}

conscell *ll_pop(conscell *list){
    if (list){
        conscell *temp = list;
        list = list->next;
        free(temp);
    }
    return list;
}

void ll_free(conscell *list) // version 1: iterative
{
    while (list != NULL) {
        conscell *p = list->next; // remember the next node
        free(list); // free the head node
        list = p; // produce a shorter list
    }
}

conscell *ll_reverse(conscell *list){
    conscell * revList = NULL;
    for (; list != NULL; list = list->next) {
        revList = ll_push(revList, list->data);
    }
    ll_free(list);
    return revList;
}

conscell *ll_sort(conscell *list, int (*cmp)(const void *a, const void *b, void *params), void *params)
{
    conscell *list1 = NULL;
    conscell *list2 = NULL;
    conscell *p, *q, *head;
    if (list == NULL)
        return list;
    head = list;
    p = list->next;
    while (p != NULL) {
        q=p->next; // remember the next node
        if (cmp(p->data, head->data, params) < 0) {
            p->next = list1;
            list1 = p;
        } else {
            p->next = list2;
            list2 = p;
        }
        p = q;
    }
    list1 = ll_sort(list1, cmp, params); // recursion
    list2 = ll_sort(list2, cmp, params); // recursion
    head->next = list2; // prepend head to list2

    if (list1 == NULL)
        return head;

    for (p = list1; p->next != NULL; p = p->next) // find list1’s tail node
        ; // empty body!
    p->next = head;
    return list1;
}

conscell *ll_filter(conscell *list, int (*filter)(const void *a), conscell **removed) {
    if (list == NULL)
        return list;
    else if (filter(list->data)) {
        conscell *p = list->next; // remember the next node
        list->next = *removed;
        *removed = list;
        return ll_filter(p, filter, removed);
    } else {
        list->next = ll_filter(list->next, filter, removed);
        return list;
    }
}

int ll_length(conscell *list) {
    conscell *new = list;
    int count = 0;
    while(new){
        count++;
        new = new->next;
    }
    return count;
}