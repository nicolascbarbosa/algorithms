// dynamic_chained_list.c
#include <stdlib.h>
#include <stdio.h>

#include "dynamic_chained_list.h"

/*
    GOODS:
        - Better memory usage;
        - Not shifting elements when insert/delete;

    BADS:
        - Expensive memory access: needs to loop over the list to access an element;
*/

struct element {
    struct person data;
    struct element *next;
};

typedef struct person person_data;
typedef struct element Element;

List* create_list() {
    List *list = (List*) malloc(sizeof(List));
    if (list != NULL)
        *list = NULL;
    return list;
}

void lfree(List *list) {
    if (list != NULL) {
        while ((*list) != NULL) {
            Element *el = *list;
            *list = (*list)->next;
            free(el);
        }
        free(list);
    }
}

int length(List *list) {
    if (list == NULL) return 0;
    int count = 0;
    Element *el = *list;
    while (el != NULL)
        count++;
        el = el->next;
    return count;
}

int is_full(List *list) {
    return 0;
}

int is_empty(List *list) {
    if (list == NULL)
        return 1;
    if (*list == NULL)
        return 1;
    return 0;
}

int prepend(List *list, person_data p) {
    if (list == NULL) return 0;
    Element *el = (Element*) malloc(sizeof(Element));
    if (el == NULL) return 0;
    el->data = p;
    el->next = (*list);
    *list = el;
    return 1;
}

int append(List *list, person_data p) {
    if (list == NULL) return 0;
    Element *el = (Element*) malloc(sizeof(Element));
    if (el == NULL) return 0;

    el->data = p;
    el->next = NULL;

    if (is_empty(list)) { // empty list, insert its first el.
        *list = el;
    } else {
        Element *aux = *list;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = el;
    }
    return 1;
}

int ordered_insert(List *list, person_data p) {
    if (list == NULL) return 0;
    Element *el = (Element*) malloc(sizeof(Element));
    if (el == NULL) return 0;

    el->data = p;

    if (is_empty(list)) { // empty list, insert its first el.
        el->next = (*list);
        *list = el;
    } else {
        Element *previous, *current = *list;
        while (current != NULL && current->data.num < p.num)
            previous = current;
            current = current->next;

        if (current == *list) { // current is null or current is less than user entry
            el->next = (*list);
            *list = el;
        } else {
            el->next = previous->next;
            previous->next = el;
        }
    }
    return 1;
}

int remove_first(List *list) {
    if (is_empty(list)) return 0;
    Element *el = *list;
    *list = el->next;
    free(el);
    return 1;
}


int remove_last(List *list) {
    if (is_empty(list)) return 0;

    Element *previous, *current = *list;
    while (current->next != NULL)
        previous = current;
        current = previous->next;

    if (current == (*list)) {
        *list = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    return 1;
}

int remove_item(List *list, int num) {
    if (is_empty(list)) return 0;

    Element *previous, *current = *list;
    while (current != NULL && current->data.num != num)
        previous = current;
        current = current->next;

    if (current == NULL) return 0; // not found :(.
    if (current == (*list)) {
        *list = current->next;
    } else {
        previous->next = current->next;
    }
    free(current);
    return 1;
}

int search_pos(List *list, int pos, struct person *p) {
    if (is_empty(list) || pos <= 0) return 0;
    Element *el = *list;
    int i = 0;
    while (el != NULL && i < pos)
        el = el->next;
        i++;
    if (el == NULL) {
        return 0;
    } else {
        *p = el->data;
    }
    return 1;
}

int search(List *list, int num, struct person *p) {
    if (is_empty(list)) return 0;

    Element *el = *list;
    while (el != NULL && el->data.num != num)
        el = el->next;

    if (el == NULL) {
        return 0;
    } else {
        *p = el->data;
    }
    return 1;
}
