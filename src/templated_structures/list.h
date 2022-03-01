#ifndef __LIST_H__
#define __LIST_H__

#include <malloc.h>

typedef struct node_t {
    void* data;
    struct node_t* next;
} node;
typedef struct list_t {
    node* head;
    int size;
} list;

list* generate_list();
void kill_list(list* list);

void push_list(list* list, void* restrict data);
void* pop_list(list* list);
void append_list(list* list, void* restrict data);
void* trim_list(list* list);

#endif /* __LIST_H__ */