#ifndef H_LINKED_LISTS_H
#define H_LINKED_LISTS_H
typedef struct conscell {
    void *data;
    struct conscell *next;
} conscell;
struct point { double x; double y; };
conscell *ll_push(conscell *list, void *data);
conscell *ll_pop(conscell *list);
void ll_free(conscell *list);   
conscell *ll_reverse(conscell *list);
conscell *ll_sort(conscell *list,
        int (*cmp)(const void *a, const void *b, void *params),
        void *params);
conscell *ll_filter(conscell *list,
        int (*filter)(const void *a),
        conscell **removed);
int ll_length(conscell *list);
#endif /* H_LINKED_LISTS_H */