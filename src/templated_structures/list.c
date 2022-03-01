#include <string.h>

#include "list.h"

static node* generate_node(void* data);

list* generate_list() {
    list* new_list = (list*)malloc(sizeof(list));
    if (new_list) {
        new_list->head = NULL;
        new_list->size = 0;
    }
    return new_list;
}

void kill_list(list* list) {
    while(list->head) {
        free(list->head->data);
        node* tmp = list->head->next;
        free(list->head);
        list->head = tmp;
    }
    free(list);
}

void push_list(list* list, void* restrict data) {
    node* new_node = generate_node(data);
    if (list->head) 
        new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void* pop_list(list* list) {
    void* return_data;
    node* tmp = list->head;
    list->head = list->head->next;

    memcpy(return_data, tmp->data, sizeof(void*));
    free(tmp->data);
    free(tmp);

    return return_data;
}

void append_list(list* list, void* restrict data) {
    node* new_node = generate_node(data);
    node* tmp = list->head;
    while(tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void* trim_list(list* list) {
    void* return_data;
    node* tmp = list->head;
    while(tmp->next)
        tmp = tmp->next;
    memcpy(return_data, tmp->data, sizeof(void*));
    free(tmp->data);
    free(tmp);
    tmp = NULL;
    return return_data;
}

static node* generate_node(void* data) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node) {
        new_node->data = data;
        new_node->next = NULL;
    }
    return new_node;
}